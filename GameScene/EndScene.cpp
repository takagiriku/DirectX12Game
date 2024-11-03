#include "EndScene.h"
#include"SceneManager.h"
#include "SafeDelete.h"
#include"GameObj/SpriteData/SpriteData.h"

void EndScene::Initialize(DirectXCommon* dxCommon, Input* input, InputCamera* inputCamera, DebugText* text, PostEffect* post, SpriteManager* SpriteMan, Audio* audio)
{
	BaseScene::Initialize(dxCommon, input, inputCamera, text, post, SpriteMan, audio);

	spriteData = new SpriteData();
	spriteData->SetStageCount(4);
	spriteData->Initialize(SpriteMan);
	
	spriteData->Signal->SetPosition({ 100,100 });
	spriteData->spriteSPACE->SetPosition({ 0,200 });
	
	post->ResetTime();
	
	audio->SoundLoadWave("se_amc04.wav");
}

void EndScene::Finalize()
{
	
}

void EndScene::Update()
{
	audio->SoundStop("digitalworld.wav");
	audio->SoundPlayWave("se_amc04.wav", true);
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
	spriteData->Signal->SetAlpha(alpha[0]);
	spriteData->spriteSPACE->SetAlpha(alpha[0]);
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

	spriteData->spriteSceneChenge->Draw();
	Sprite::PostDraw();
}

void EndScene::FirstDraw2D()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	//
	Sprite::PreDraw(cmdList);
	spriteData->Signal->Draw();
	spriteData->spriteSPACE->Draw();
	Sprite::PostDraw();
}

void EndScene::DrawImGui()
{
}
