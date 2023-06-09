#pragma once
#include "BaseScene.h"
class EndScene :
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
    Sprite* Signal = nullptr;
    Sprite* spriteSceneChenge = nullptr;
    Sprite* spriteSPACE = nullptr;
    float alpha[3] = { 0,0,0 };  // 初期のアルファ
    float speed = 0.005f; // 点滅の速度
};

