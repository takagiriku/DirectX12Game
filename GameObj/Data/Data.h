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
class ParticleManager;
class PostEffect;
// ステージデータ
struct StageData {
    uint32_t BatteryNum;  //class Battery
    uint32_t KeyNum;      //class Key
    uint32_t TitleObjNum; //object TitleObjs
    uint32_t TitleMoveNum;//object TitleMove
    uint32_t RandBlockNum;//class BlockObj;
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
    void Update(PostEffect* post, ParticleManager* particleMan);
    
    //ステージカウント
    void SetStageCount(uint32_t Count) { this->StageCount = Count; }
    uint32_t StageCount = 0;

    Light* light = nullptr;
    ParticleManager* particleMan = nullptr;
    PostEffect* post = nullptr;

    //モデル
    Model* mKey = nullptr;
    Model* mBattery = nullptr;
    Model* mDome = nullptr;
    Model* mPlayerBody = nullptr;
    Model* mPlayer = nullptr;
    Model* mTitleObjs = nullptr;
    Model* mTitleMove = nullptr;
    Model* mBlockObj = nullptr;

    //オブジェクト
    Key* Keys[obj];
    Battery* battery[obj];
    Object3d* TitleObjs[obj];
    Object3d* TitleMove[obj];
    Object3d* Dome = nullptr;
    Player* objPlayerBody = nullptr;
    PlayerHead* objPlayer = nullptr;
    BlockObj* objblock[10];
    
    
    
    SpriteManager* SpriteMan = nullptr;

    const int obj = 10;
};

