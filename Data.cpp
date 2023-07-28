#include "Data.h"
#include"GameObj/Key/Key.h"
#include"GameObj/Battery/Battery.h"
#include"GameObj/Box/Box.h"
#include"GameObj/Backobj/Backobj.h"
#include"GameObj/Player/Player.h"
#include"GameObj/Player/PlayerHead.h"
#include"GameObj/Tile/Tile.h"
#include"2d/SpriteManager.h"
//ToDo データをまとめる
StageData stageDatas[StageNum] = {
    { 1, 1, 9, 2, 0, 0, 0}, // チュートリアル
    { 8, 1, 0, 0, 0, 0, 0}, // ステージ1
    { 4, 1, 0, 0, 4, 4, 8},//ステージ2
    { 0 ,0, 0, 2, 0, 0, 0},//クリアステージ
    { 0 ,0, 0, 0, 0, 0, 0}//ゲームオーバー
};

void Data::Initialize()
{

   /* spriteSceneChenge = new Sprite;
    spriteSPACE = new Sprite;
    TITLE = new Sprite;
    Black = new Sprite;
    Signal = new Sprite;

    SpriteMan->LoadTexture(0, L"Resources/SPACE.png");
    SpriteMan->LoadTexture(1, L"Resources/scenechenge.png");
    SpriteMan->LoadTexture(2, L"Resources/TITLE.png");
    SpriteMan->LoadTexture(3, L"Resources/black.png");
    SpriteMan->LoadTexture(4, L"Resources/Signal.png");

    spriteSPACE->Create(0);
    spriteSceneChenge->Create(1);
    TITLE->Create(2);
    Black->Create(3);
    Signal->Create(4);*/
    
    mKey = Model::CreateOBJ("key");
    mBattery = Model::CreateOBJ("Battery");
    mBox = Model::CreateOBJ("Box");
    mBBox = Model::CreateOBJ("BlackBox");
    mDome = Model::CreateOBJ("skydome");
    mPlayerBody = Model::CreateOBJ("playerbody");
    mPlayer = Model::CreateOBJ("playerobj");
    mTitleObjs = Model::CreateOBJ("TitleObjs");
    mTitleMove = Model::CreateOBJ("titleobj");
    mTile = Model::CreateOBJ("Gole");
    //mBack = Model::CreateOBJ("BackObj");
    
   

    int i = StageCount;

    if (stageDatas[i].KeyNum)
    {
        for (int j = 0; j < stageDatas[i].KeyNum; j++) { Keys[j] = Key::Create(mKey); }
    }
    else
    {
        Keys[i] = nullptr;
    }
    if (stageDatas[i].BatteryNum)
    {
        for (int j = 0; j < stageDatas[i].BatteryNum; j++) { battery[j] = Battery::Create(mBattery); }
    }
    else
    {
        battery[i] = nullptr;
    }
    if (stageDatas[i].TitleObjNum)
    {
        for (int j = 0; j < stageDatas[i].TitleObjNum; j++) { TitleObjs[j] = Object3d::Create(mTitleObjs); }
    }
    else
    {
        TitleObjs[i] = nullptr;
    }
    if (stageDatas[i].TitleMoveNum)
    {
        for (int j = 0; j < stageDatas[i].TitleMoveNum; j++) { TitleMove[j] = Object3d::Create(mTitleMove); }
    }
    else
    {
        TitleMove[i] = nullptr;
    }
    if (stageDatas[i].BoxNum)
    {
        for (int j = 0; j < stageDatas[i].BoxNum; j++) { Box[j] = Box::Create(mBox); }
    }
    else
    {
        Box[i] = nullptr;
    }
    if (stageDatas[i].BBoxNum)
    {
        for (int j = 0; j < stageDatas[i].BBoxNum; j++) { BBox[j] = Object3d::Create(mBBox); }
    }
    else
    {
        BBox[i] = nullptr;
    }
    if (stageDatas[i].TileNum)
    {
        for (int j = 0; j < stageDatas[i].TileNum; j++) { Tile[j] = Tile::Create(mTile); }
    }
    else
    {
        Tile[i] = nullptr;
    }
    objPlayerBody = Player::Create(mPlayerBody);
    objPlayer = PlayerHead::Create(mPlayer);
    
    Dome = Object3d::Create(mDome);
    
}

void Data::Finalize()
{
    safe_delete(Dome);
    safe_delete(mDome);
    safe_delete(mKey);
    safe_delete(mBattery);
    safe_delete(objPlayerBody);
    safe_delete(objPlayer);
    safe_delete(mPlayerBody);
    safe_delete(mPlayer);
    safe_delete(mTile);
    
    safe_delete(mBox);
    safe_delete(mBox);
    safe_delete(mTitleObjs);    
    safe_delete(mTitleMove);

    for (int i = 0; i < 10; i++)
    {
        safe_delete(Box[i]);
        safe_delete(BBox[i]);
        safe_delete(TitleObjs[i]);
        safe_delete(TitleMove[i]);
        safe_delete(Tile[i]);
        safe_delete(Keys[i]);
    }
}

void Data::Update()
{
    int i = StageCount;
}
