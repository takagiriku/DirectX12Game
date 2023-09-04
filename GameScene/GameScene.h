#pragma once
#include <DirectXMath.h>
#include"BaseScene.h"
#include "SceneFactory.h"
#include"GameObj/Stage/Stage.h"
#include"GameObj/Key/Key.h"
#include"GameObj/Battery/Battery.h"
#include"ParticleManager.h"


class Player;
class PlayerHead;
class Data;
class GameScene : public BaseScene
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
    bool AlphaFlag = false;
    bool anyTrue = false; // trueの要素が存在するかを示す変数
    float alpha[3] = { 0,0,0 };
    XMFLOAT3 PBodyPosition = { 6,2,0 };
    XMFLOAT3 PHeadPosition = { 0,0,0 };
    XMFLOAT3 CameraPosition = { -15,15,-15 };
    XMFLOAT3 KeyPosition = { 60,15,10 };
    XMFLOAT3 BatteryPosition[10] = {
    { 120,3,0 },
    { 120,3,72 },
    { 5,3,72 },
    { 65,3,6 },
    { 103,3,67 },
    { 3,13,0 },
    { 121,13,0 },
    { 120,13,72 },
    { 83,13,31 },
    { 83,13,67 }
    };

    float PlayerBodyRotx = 0;
    float PlayerBodyRoty = 0;
    float PlayerBodyRotz = 0;

    float PlayerPos[3] = { 0, 0.0f, 0 };
    float CameraPos[3] = { 0, 0.0f, 0 };
    float KeyPos[3] = { 0, 0.0f, 0 };
  
    float SpriteX[2] = { 1280,1280 };
    float SpriteY[2] = { 740,0 };
    // 視点座標
    float Eye[3] = { 0, 0, 0 };
    float Time[1] = { 0 };
    
    Stage* stage = nullptr;
    Light* light = nullptr;
    Sprite* spriteSceneChenge = nullptr;
    Sprite* Black = nullptr;
    
    ParticleManager* particleMan = nullptr;

    Data* data = nullptr;
};

