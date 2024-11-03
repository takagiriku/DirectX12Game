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
class BlackObj;
class SpriteData;
class RandomStageScene : public BaseScene
{
private:
    // �G�C���A�X
    template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
    using XMFLOAT2 = DirectX::XMFLOAT2;
    using XMFLOAT3 = DirectX::XMFLOAT3;
    using XMFLOAT4 = DirectX::XMFLOAT4;
    using XMVECTOR = DirectX::XMVECTOR;
    using XMMATRIX = DirectX::XMMATRIX;

public:

    // ������
    void Initialize(DirectXCommon* dxCommon, Input* input, InputCamera* inputCamera, DebugText* text, PostEffect* post, SpriteManager* SpriteMan, Audio* audio) override;


    // �I��
    void Finalize() override;

    // ���t���[��
    void Update() override;

    // �`��
    void Draw() override;

    void Draw2D() override;

    void FirstDraw2D() override;

    void DrawImGui() override;


private:

    bool StartFlag = false;
    bool AlphaFlag = false;

    float alpha[3] = { 0,0,0 };
    
    //�e���W
    XMFLOAT3 PBodyPosition = { 6,2,0 };
    XMFLOAT3 PHeadPosition = { 0,0,0 };
    XMFLOAT3 CameraPosition = { -15,3,-25 };
    XMFLOAT3 KeyPosition = { 242,5,10 };
    XMFLOAT3 BatteryPosition[10] = {
    { 5,3,72 },
    { 5,3,0 },
    { 120,3,0 },
    { 120,3,72 },
    { 240,3,72 },
    { 240,3,0 },
    { 360,3,0 },
    { 360,3,72 },
    { 480,3,0 },
    { 480,3,72 }
    };
    
    //ImGui�p
    float PlayerPos[3] = { 0, 0.0f, 0 };
    float CameraPos[3] = { 0, 0.0f, 0 };
    float KeyPos[3] = { 0, 0.0f, 0 };
    

    float SpriteX[2] = { 1280,1280 };
    float SpriteY[2] = { 740,0 };
    // ���_���W
    float Eye[3] = { 0, 0, 0 };
    float Time[1] = { 0 };

    Stage* stage = nullptr;
    Light* light = nullptr;
  
    ParticleManager* particleMan = nullptr;

    Data* data = nullptr;
    SpriteData* spriteData = nullptr;
};

