#pragma once
#include <DirectXMath.h>
#include"BaseScene.h"
#include "SceneFactory.h"
#include"GameObj/Stage/Stage.h"
#include"GameObj/Key/Key.h"
#include"GameObj/Battery/Battery.h"
#include"GameObj/Box/Box.h"
#include"GameObj/Tile/Tile.h"
#include"ParticleManager.h"


class Player;
class PlayerHead;
class Data;
class GameScene2 : public BaseScene
{
private:
    // エイリアス
    template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
    using XMFLOAT2 = DirectX::XMFLOAT2;
    using XMFLOAT3 = DirectX::XMFLOAT3;
    using XMFLOAT4 = DirectX::XMFLOAT4;
    using XMVECTOR = DirectX::XMVECTOR;
    using XMMATRIX = DirectX::XMMATRIX;

public:

    // 初期化
    void Initialize(DirectXCommon* dxCommon, Input* input, InputCamera* inputCamera, DebugText* text, PostEffect* post, SpriteManager* SpriteMan, Audio* audio) override;


    // 終了
    void Finalize() override;

    // 毎フレーム
    void Update() override;

    // 描画
    void Draw() override;

    void Draw2D() override;

    void FirstDraw2D() override;

    void DrawImGui() override;


private:

    bool StartFlag = false;
    bool AlphaFlag = true;
    bool anyTrue = false; // trueの要素が存在するかを示す変数
    float alpha[3] = { 0,0,0 };
    XMFLOAT3 PBodyPosition = { 18,11,-18 };
    XMFLOAT3 PHeadPosition = { 0,0,0 };
    XMFLOAT3 CameraPosition = { -15,15,-15 };
    XMFLOAT3 KeyPosition = { 0,-10,0 };
    XMFLOAT3 BatteryPosition[4] = {
    { 101,13,17 },
    { 25, 13,17 },
    { 26, 13,54 },
    { 101,13,54 }
    };
    XMFLOAT3 BoxPosition[4] = {
    { 107,12,38 },
    { 124,12,25 },
    { 25, 12,73 },
    { 10, 12,1 }
    };
    XMFLOAT3 BBoxPosition[4] = {
    { 1,  10,1 },
    { 124,10,1 },
    { 1,  10,73 },
    { 124,10,73 },
    }; XMFLOAT3 TilePosition[8] = {
    { 1,  11.1,1 },
    { 1,  11.1,1 },
    { 124,11.1,1 },
    { 124,11.1,1 },
    { 1,  11.1,73 },
    { 1,  11.1,73 },
    { 124,11.1,73 },
    { 124,11.1,73 },
    };

    float Time = 0;
    float FlagCount[4] = { 0,0,0,0 };
    bool allFlagsTrue = true;

    float PlayerBodyRotx = 0;
    float PlayerBodyRoty = 0;
    float PlayerBodyRotz = 0;

    float PlayerPos[3] = { 0, 0.0f, 0 };
    float CameraPos[3] = { 0, 0.0f, 0 };
    float KeyPos[3] = { 0, 0.0f, 0 };
    float BatPos[3] = { 0, 0.0f, 0 };

    //影の位置
    int PlayerShadow[3] = { 0,0,0 };
    //影の減衰距離
    int PlayerShadowDir[3] = { 0,0,0 };
    int PlayerLight[3] = { 0,0,0 };
    int time = 0;
    float ambientColor0[3] = { 1,1,1 };
    // 光線方向初期値
    float lightDir0[3] = { 0,0,1 };
    float lightColor0[3] = { 0,1,0 };
    //方向
    float lightDir1[3] = { 1,1,0 };
    float lightColor1[3] = { 0,1,0 };
    float lightDir2[3] = { 1,0,0 };
    float lightColor2[3] = { 0,0,1 };
    float spotLightDir[3] = { 0,-1,0 };
    float spotLightPos[3] = { 0,5,0 };
    float spotLightColor[3] = { 0.7f,0.8f,1 };
    float spotLightAtten[3] = { 0.0f,0.0f,0.0f };
    float spotLightFactorAngle[2] = { 20.0f, 30.0f };

    float circleShadowDir[3] = { 0,-1,0 };
    float circleShadowPos[3] = { 1,7,0 };
    float circleShadowAtten[3] = { 0.5f,0.6f,0.0f };
    float circleShadowFactorAngle[2] = { 0.0f, 0.5f };
    float tests[3] = { 0,0,0 };
    XMFLOAT3 test = { 0,0,0 };

    float SpriteX[2] = { 1280,1280 };
    float SpriteY[2] = { 740,0 };
    // 視点座標
    float Eye[3] = { 0, 0, 0 };
    

    Battery* Battery[4];
    Stage* stage = nullptr;
    Light* light = nullptr;
    ParticleManager* particleMan = nullptr;
    Sprite* spriteSceneChenge = nullptr;
    Sprite* Black = nullptr;
    
    Data* data = nullptr;
};

