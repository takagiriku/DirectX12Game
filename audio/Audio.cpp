#include "Audio.h"
#include <fstream>
#include <cassert>
#include <iostream>

#pragma comment(lib,"xaudio2.lib")

Audio::~Audio()
{
    // サウンドの解放
    SoundUnload();

    // マスターボイスの解放
    if (masterVoice)
    {
        masterVoice->DestroyVoice();
        masterVoice = nullptr;
    }

    // XAudio2の解放
    if (xAudio2)
    {
        xAudio2->Release();
        xAudio2 = nullptr;
    }
}


bool Audio::Initialize()
{
    HRESULT result;

    // XAudioエンジンのインスタンスを生成
    result = XAudio2Create(&xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
    if (FAILED(result)) {
        std::cerr << "Failed to initialize XAudio2." << std::endl;
        return false;
    }

    // マスターボイスを生成
    result = xAudio2->CreateMasteringVoice(&masterVoice);
    if (FAILED(result)) {
        std::cerr << "Failed to create mastering voice." << std::endl;
        return false;
    }

    return true;
}

// サウンド読み込み
void Audio::SoundLoadWave(const char* filename)
{
    // ファイル入力ストリームのインスタンス
    std::ifstream file;
    // .wavファイルをバイナリモードで開く
    file.open(baseDirectory + filename, std::ios_base::binary);
    // ファイルオープン失敗を検出する
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    // RIFFヘッダーの読み込み
    RiffHeader riff;
    file.read((char*)&riff, sizeof(riff));
    // ファイルがRIFFかチェック
    if (std::string(riff.chunk.id, 4) != "RIFF") {
        std::cerr << "Invalid RIFF header." << std::endl;
        file.close();
        return;
    }
    // タイプがWAVEかチェック
    if (std::string(riff.type, 4) != "WAVE") {
        std::cerr << "Invalid WAVE type." << std::endl;
        file.close();
        return;
    }

    // Formatチャンクの読み込み
    FormatChunk format = {};
    // チャンクヘッダーの確認
    file.read((char*)&format, sizeof(ChunkHeader));
    if (std::string(format.chunk.id, 4) != "fmt ") {
        std::cerr << "Invalid format chunk." << std::endl;
        file.close();
        return;
    }
    // チャンク本体の読み込み
    assert(format.chunk.size <= sizeof(format.fmt));
    file.read((char*)&format.fmt, format.chunk.size);

    // Dataチャンクの読み込み
    ChunkHeader data;
    file.read((char*)&data, sizeof(data));
    // JUNKチャンクを検出した場合
    if (std::string(data.id, 4) == "JUNK") {
        // 読み取り位置をJUNKチャンクの終わりまで進める
        file.seekg(data.size, std::ios_base::cur);
        // 再読み込み
        file.read((char*)&data, sizeof(data));
    }
    if (std::string(data.id, 4) != "data") {
        std::cerr << "Invalid data chunk." << std::endl;
        file.close();
        return;
    }
    // Dataチャンクのデータ部（波形データ）の読み込み
    char* pBuffer = new char[data.size];
    file.read(pBuffer, data.size);

    // Waveファイルを閉じる
    file.close();

    // returnする為の音声データ
    SoundData soundData = {};

    soundData.wfex = format.fmt;
    soundData.pBuffer = reinterpret_cast<BYTE*>(pBuffer);
    soundData.bufferSize = data.size;

    // ファイル名で登録
    soundDatas.emplace(filename, soundData);

    HRESULT result;

    // 波形フォーマットを元にSourceVoiceの生成
    IXAudio2SourceVoice* pSourceVoice = nullptr;
    result = xAudio2->CreateSourceVoice(&pSourceVoice, &soundDatas[filename].wfex);
    if (FAILED(result)) {
        std::cerr << "Failed to create source voice." << std::endl;
        return;
    }

    // ファイル名で登録
    pSourceVoices.emplace(filename, pSourceVoice);
}

void Audio::SoundUnload()
{
    // バッファのメモリを解放
    for (auto& soundData : soundDatas) {
        delete[] soundData.second.pBuffer;
    }
    soundDatas.clear();
    pSourceVoices.clear();
}

// 再生
void Audio::SoundPlayWave(const char* filename, bool loopFlag)
{
    if (soundDatas.find(filename) == soundDatas.end()) {
        std::cerr << "Sound data not found: " << filename << std::endl;
        return;
    }

    HRESULT result;

    // 再生する波形データの設定
    XAUDIO2_BUFFER buf{};
    buf.pAudioData = soundDatas[filename].pBuffer;
    buf.AudioBytes = soundDatas[filename].bufferSize;
    buf.Flags = XAUDIO2_END_OF_STREAM;
    if (loopFlag) {
        buf.LoopCount = XAUDIO2_LOOP_INFINITE;
    }

    // 波形データの再生
    result = pSourceVoices[filename]->FlushSourceBuffers();
    if (FAILED(result)) {
        std::cerr << "Failed to flush source buffers." << std::endl;
        return;
    }
    result = pSourceVoices[filename]->SubmitSourceBuffer(&buf);
    if (FAILED(result)) {
        std::cerr << "Failed to submit source buffer." << std::endl;
        return;
    }
    result = pSourceVoices[filename]->Start();
    if (FAILED(result)) {
        std::cerr << "Failed to start source voice." << std::endl;
        return;
    }
}

// 再生を止める
void Audio::SoundStop(const char* filename)
{
    if (pSourceVoices.find(filename) == pSourceVoices.end()) {
        std::cerr << "Source voice not found: " << filename << std::endl;
        return;
    }

    pSourceVoices[filename]->Stop();
}
