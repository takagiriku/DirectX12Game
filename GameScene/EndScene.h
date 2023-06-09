#pragma once
#include "BaseScene.h"
class EndScene :
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
    Sprite* Signal = nullptr;
    Sprite* spriteSceneChenge = nullptr;
    Sprite* spriteSPACE = nullptr;
    float alpha[3] = { 0,0,0 };  // �����̃A���t�@
    float speed = 0.005f; // �_�ł̑��x
};

