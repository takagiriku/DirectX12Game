#pragma once

#define DIRECTINPUT_VERSION 0x0800          // DirectInputのバージョン指定

#include <Windows.h>
#include <wrl.h>
#include <dinput.h>
// 入力
class Input
{
public:
	
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // 静的メンバ変数
	static Input* GetInstance();

public: // メンバ関数
	
	// 初期化
	bool Initialize(HINSTANCE hInstance, HWND hwnd);

	// 毎フレーム処理
	void Update();

	// キーの押下をチェック
	bool Push(BYTE keyNumber);

	// キーのトリガーをチェック
	bool Trigger(BYTE keyNumber);

	


private: // メンバ変数
	ComPtr<IDirectInput8> dinput;
	ComPtr<IDirectInputDevice8> devKeyboard;
	BYTE key[256] = {};
	BYTE keyPre[256] = {};

};

