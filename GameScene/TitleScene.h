#pragma once

#include <DirectXMath.h>
#include "BaseScene.h"
#include "SceneFactory.h"
#include "2d/PostEffect.h"
#include "ParticleManager.h"

class Player;
class PlayerHead;
class Key;
class Stage;
class Battery;
class GameManager;
class Data;
class SpriteData;

class TitleScene : public BaseScene
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
    // �t���O
    bool StartFlag = false;

    // �e���W
    XMFLOAT3 PBodyPosition = { 0, 70, 7 };
    XMFLOAT3 PBodyRotation = { 0, 0, 0 };
    XMFLOAT3 PHeadPosition = { 0, 0, 0 };
    XMFLOAT3 CameraPosition = { -15, 15, -15 };
    XMFLOAT3 KeyPosition = { -8, 5, 67 };
    XMFLOAT3 BatteryPosition = { 8, 3, 45 };

    // ImGui�p
    float PlayerPos[3] = { 0, 0, 0 };
    float CameraPos[3] = { 0, 0, 0 };
    float KeyPos[3] = { 0, 0, 0 };
    float SpriteX[2] = { 0, 1280 };
    float SpriteY[2] = { 0, 0 };

    // ���_���W
    float Eye[3] = { 0, 0, 0 };

    // �Q�[���I�u�W�F�N�g
    Stage* stage = nullptr;
    ParticleManager* particleMan = nullptr;
    Sprite* spriteSceneChange = nullptr;
    Sprite* spriteSPACE = nullptr;
    Sprite* TITLE = nullptr;

    // �A���t�@�l
    float alpha[3] = { 0, 0, 0 };  // �����̃A���t�@
    float a[3] = { 0,0,0 };
    float speed = 0.005f; // �_�ł̑��x
    float count[1] = { 0 };

    // �f�[�^
    Data* data = nullptr;
    SpriteData* spriteData = nullptr;
};