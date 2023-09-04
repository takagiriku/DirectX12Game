#pragma once
#pragma once
#include <DirectXMath.h>
#include "BaseScene.h"
#include "SceneFactory.h"
#include"2d/PostEffect.h"
#include "ParticleManager.h"
#include"Data.h"
class Player;
class PlayerHead;
class Key;
class Stage;
class Battery;
class GameManager;
class Data;
class TitleScene : public BaseScene
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
    float a[3] = { 0,0,0 };
    XMFLOAT3 PBodyPosition = { 0,70,7 };
    XMFLOAT3 PBodyRotation = { 0,0,0 };
    XMFLOAT3 PHeadPosition = { 0,0,0 };
    XMFLOAT3 CameraPosition = { -15,15,-15 };
    XMFLOAT3 KeyPosition = { -8,5,67 };
    XMFLOAT3 BatteryPosition = { 8,3,45};
   
    float PlayerBodyRotx = 0;
    float PlayerBodyRoty = 0;
    float PlayerBodyRotz = 0;

    float PlayerPos[3] = { 0, 0, 0 };
    float CameraPos[3] = { 0, 0, 0 }; 
    float KeyPos[3] = { 0, 0, 0 };
    
    float SpriteX[2] = { 0,1280 };
    float SpriteY[2] = { 0,0 };
    // 視点座標
    float Eye[3] = { 0, 0, 0 };
    
    Model* mBack = nullptr;
    
 
    Stage* stage = nullptr;
    Light* light = nullptr;
    ParticleManager* particleMan = nullptr;
    Sprite* spriteSceneChenge = nullptr;
    Sprite* spriteSPACE = nullptr;
    Sprite* TITLE = nullptr;
    Sprite* Black = nullptr;
  
    float alpha[3] = {0,0,0};  // 初期のアルファ
    float speed = 0.005f; // 点滅の速度
    float count[1]={0};

    Data* data = nullptr;
};