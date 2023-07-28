#pragma once
#include "BaseScene.h"
#include "SceneFactory.h"
#include"GameObj/Stage/Stage.h"

class Player;
class PlayerHead;
class Data;
class ClearScene :
    public BaseScene
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
    bool EndFlag = false;
    bool AlphaFlag = true;
    XMFLOAT3 PBodyPosition = { 1,1,0 };
    XMFLOAT3 PHeadPosition = { 0,0,0 };
    XMFLOAT3 CameraPosition = { -15,15,-15 };
    XMFLOAT3 TitlePosition[2] = { { -1,3,60 },{2,3,60} };
    float PlayerBodyRotx = 0;
    float PlayerBodyRoty = 0;
    float PlayerBodyRotz = 0;
    float Time = 0;
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
    // 視点座標
    float Eye[3] = { 0, 0, 0 };
    float SpriteX[2] = { 1280,1280 };
    float SpriteY[2] = { 740,0 };
    float PlayerPos[3] = { 0, 0.0f, 0 };
    
    Sprite* spriteSceneChenge = nullptr;
    Sprite* Black = nullptr;
    Light* light = nullptr;
    Stage* stage = nullptr;
    float alpha[3] = { 0,0,0 };
    float test[1] = {0};
    Data* data = nullptr;
};