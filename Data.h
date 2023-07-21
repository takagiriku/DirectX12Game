#pragma once
#include <cstdint>

// ステージデータ
struct StageData {
    uint32_t itemNum;
    uint32_t KeyNum;
    uint32_t BoxNum;

};
// ステージ数
const uint32_t StageNum = 5;

class Data
{
    // 初期化
    void Initialize();

    // 終了
    void Finalize();

    // 毎フレーム
    void Update();

    

};

