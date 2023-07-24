#pragma once
#include <cstdint>
#include"2d/Sprite.h"
#include <3d/Model.h>
#include "3d/Object3d.h"

class Key;
class Battery;
class Box;
class Player;
class PlayerHead;
class BackObj;
class Tile;
// ステージデータ
struct StageData {
    uint32_t itemNum;
    uint32_t KeyNum;
    uint32_t BoxNum;

};
// ステージ数
const uint32_t StageNum = 5;
const uint32_t StageCount = 0;
class Data
{
public:
    // 初期化
    void Initialize();

    // 終了
    void Finalize();

    // 毎フレーム
    void Update();
    
    Model* mKey = nullptr;
    Model* mBattery = nullptr;
    Model* mBox = nullptr;
    Model* mBBox = nullptr;
    Model* mDome = nullptr;
    Model* modelPlayerBody = nullptr;
    Model* modelPlayer = nullptr;
    Model* modelTitleObjs = nullptr;
    Model* mTitleMove = nullptr;
    Model* mTile = nullptr;
    Model* mBack = nullptr;

    Key* Keys[StageNum];
    Battery* battery[StageNum];
    Box* box[StageNum];
    Object3d* BBox[4];
    Tile* Tile[8];
    Player* objPlayerBody = nullptr;
    PlayerHead* objPlayer = nullptr;
    const int obj = 10;
    BackObj* objBack[10];
    Object3d* TitleObjs[10];
    Object3d* TitleMove[2];
    Object3d* Dome = nullptr;


    Sprite* spriteSceneChenge = nullptr;
    Sprite* spriteSPACE = nullptr;
    Sprite* TITLE = nullptr;
    Sprite* Black = nullptr;
    Sprite* Signal = nullptr;
  
};

