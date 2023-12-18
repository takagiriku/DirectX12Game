#pragma once
#include"2d/Sprite.h"
#include"2d/SpriteManager.h"
//スプライトデータ
struct SpriteDatas{
    bool ChangeNum;//シーン変更につかう
    bool BlackNum; //一気に暗くするのに使う
    bool SpaceNum; //Spaceロゴ
    bool TitleNum; //タイトルロゴ
    bool SignalNum;//ゲームオーバーに使う
};

class SpriteData
{
public:
    // 初期化
    void Initialize(SpriteManager* SpriteMan);
    //毎フレーム処理
    void Update();
    //ステージカウント
    void SetStageCount(uint32_t Count) { this->StageCount = Count; }
    uint32_t StageCount = 0;

    Sprite* spriteSceneChenge = nullptr;
    Sprite* spriteSPACE = nullptr;
    Sprite* TITLE = nullptr;
    Sprite* Black = nullptr;
    Sprite* Signal = nullptr;
};

