#include "EndScene.h"
#include"SceneManager.h"
#include "SafeDelete.h"


void EndScene::Initialize(DirectXCommon* dxCommon, Input* input, InputCamera* inputCamera, DebugText* text, PostEffect* post, SpriteManager* SpriteMan, Audio* audio)
{
	BaseScene::Initialize(dxCommon, input, inputCamera, text, post, SpriteMan, audio);


	SpriteMan->LoadTexture(0, L"Resources/No Signal.png");
	Signal = new Sprite();
	Signal->Create(0);
	Signal->SetPosition({ 100,100 });
	SpriteMan->LoadTexture(1, L"Resources/scenechenge.png");
	spriteSceneChenge = new Sprite();
	spriteSceneChenge->Create(1);

	SpriteMan->LoadTexture(2, L"Resources/SPACE.png");
	spriteSPACE = new Sprite();
	spriteSPACE->Create(2);
	spriteSPACE->SetPosition({ 0,200 });
	post->SetPostFlag(true);
}

void EndScene::Finalize()
{
	safe_delete(Signal);
	safe_delete(spriteSPACE);
	safe_delete(spriteSceneChenge);
}

void EndScene::Update()
{
	if (input->Push(DIK_SPACE))
	{
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}

	alpha[0] += speed;  // アルファ値を変化させる

	if (alpha[0] > 1.0f)
	{
		alpha[0] = 1.0f;
		speed *= -1;  // アルファ値が1.0を超えた場合は反転する
	}
	else if (alpha[0] < 0.0f)
	{
		alpha[0] = 0.0f;
		speed *= -1;  // アルファ値が0.0を下回った場合も反転する
	}
	Signal->SetAlpha(alpha[0]);
	spriteSPACE->SetAlpha(alpha[0]);
}

void EndScene::Draw()
{
}

void EndScene::Draw2D()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	//
	Sprite::PreDraw(cmdList);

	spriteSceneChenge->Draw();
	Sprite::PostDraw();
}

void EndScene::FirstDraw2D()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	//
	Sprite::PreDraw(cmdList);
	Signal->Draw();
	spriteSPACE->Draw();
	Sprite::PostDraw();
}

void EndScene::DrawImGui()
{
}
