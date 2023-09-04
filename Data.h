#pragma once
#include <cstdint>
#include"2d/Sprite.h"
#include <3d/Model.h>
#include "3d/Object3d.h"
#include "BaseScene.h"
class Key;
class Battery;
class Player;
class PlayerHead;
class BlockObj;
// ステージデータ
struct StageData {
    uint32_t BatteryNum;
    uint32_t KeyNum;
    uint32_t TitleObjNum;
    uint32_t TitleMoveNum;
};
struct LightData {
    uint32_t SpotLightNum;
    uint32_t PointLightNum;
    uint32_t ShadowNum;
};

// ステージ数
const uint32_t StageNum = 5;

const uint32_t obj = 10;
class Data
{
public:
    // 初期化
    void Initialize();

    // 終了
    void Finalize();

    // 毎フレーム
    void Update();
    
    void SetStageCount(uint32_t Count) { this->StageCount = Count; }
    uint32_t StageCount = 0;

    Light* light = nullptr;

    Model* mKey = nullptr;
    Model* mBattery = nullptr;
    Model* mDome = nullptr;
    Model* mPlayerBody = nullptr;
    Model* mPlayer = nullptr;
    Model* mTitleObjs = nullptr;
    Model* mTitleMove = nullptr;
    Model* mBlockObj = nullptr;

    Key* Keys[obj];
    Battery* battery[obj];
    Object3d* TitleObjs[obj];
    Object3d* TitleMove[obj];
    
    Player* objPlayerBody = nullptr;
    PlayerHead* objPlayer = nullptr;
    const int obj = 10;
    
    BlockObj* objblock[10];
    
    Object3d* Dome = nullptr;


    Sprite* spriteSceneChenge = nullptr;
    Sprite* spriteSPACE = nullptr;
    Sprite* TITLE = nullptr;
    Sprite* Black = nullptr;
    Sprite* Signal = nullptr;
  
    SpriteManager* SpriteMan = nullptr;
};

