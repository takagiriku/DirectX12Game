#pragma once
#include <cstdint>
#include"2d/Sprite.h"
#include <3d/Model.h>
#include "3d/Object3d.h"
#include "BaseScene.h"
class Key;
class Battery;
class Box;
class Player;
class PlayerHead;
class BackObj;
class Tile;

// ステージデータ
struct StageData {
    uint32_t BatteryNum;
    uint32_t KeyNum;
    uint32_t TitleObjNum;
    uint32_t TitleMoveNum;
    uint32_t BoxNum;
    uint32_t BBoxNum;
    uint32_t TileNum;

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


    Model* mKey = nullptr;
    Model* mBattery = nullptr;
    Model* mBox = nullptr;
    Model* mBBox = nullptr;
    Model* mDome = nullptr;
    Model* mPlayerBody = nullptr;
    Model* mPlayer = nullptr;
    Model* mTitleObjs = nullptr;
    Model* mTitleMove = nullptr;
    Model* mTile = nullptr;
    //Model* mBack = nullptr;

    Key* Keys[obj];
    Battery* battery[obj];
    Box* Box[obj];
    Object3d* TitleObjs[obj];
    Object3d* TitleMove[obj];
    Object3d* BBox[obj];
    Tile* Tile[obj];

    Player* objPlayerBody = nullptr;
    PlayerHead* objPlayer = nullptr;
    const int obj = 10;
    //BackObj* objBack[10];
    
    
    Object3d* Dome = nullptr;


    Sprite* spriteSceneChenge = nullptr;
    Sprite* spriteSPACE = nullptr;
    Sprite* TITLE = nullptr;
    Sprite* Black = nullptr;
    Sprite* Signal = nullptr;
  
    SpriteManager* SpriteMan = nullptr;
};

