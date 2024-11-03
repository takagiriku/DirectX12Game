#pragma once
#include "BaseScene.h"
#include "SceneFactory.h"
#include"GameObj/Stage/Stage.h"

class Player;
class PlayerHead;
class Data;
class SpriteData;
class ClearScene :
    public BaseScene
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
    bool EndFlag = false;
    bool AlphaFlag = true;
    //�e���W
    XMFLOAT3 PBodyPosition = { 1,1,0 };
    XMFLOAT3 PHeadPosition = { 0,0,0 };
    XMFLOAT3 CameraPosition = { -15,15,-15 };
    XMFLOAT3 TitlePosition[2] = { { -1,3,60 },{2,3,60} };
    float Time = 0;
  
    //ImGui�p
    // ���_���W
    float Eye[3] = { 0, 0, 0 };
    float SpriteX[2] = { 1280,1280 };
    float SpriteY[2] = { 740,0 };
    float PlayerPos[3] = { 0, 0.0f, 0 };
    
    
    Light* light = nullptr;
    Stage* stage = nullptr;

    float alpha[3] = { 0,0,0 };
    float PostTime[1] = {0};
    Data* data = nullptr;
    SpriteData* spriteData = nullptr;
};