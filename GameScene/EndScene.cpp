#include "EndScene.h"
#include"SceneManager.h"
#include "SafeDelete.h"
#include"GameObj/SpriteData/SpriteData.h"

void EndScene::Initialize(DirectXCommon* dxCommon, Input* input, InputCamera* inputCamera, DebugText* text, PostEffect* post, SpriteManager* SpriteMan, Audio* audio)
{
	BaseScene::Initialize(dxCommon, input, inputCamera, text, post, SpriteMan, audio);

	spritedata = new SpriteData();
	spritedata->SetStageCount(4);
	spritedata->Initialize(SpriteMan);
	
	spritedata->Signal->SetPosition({ 100,100 });
	spritedata->spriteSPACE->SetPosition({ 0,200 });
	
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

	alpha[0] += speed;  // �A���t�@�l��ω�������

	if (alpha[0] > 1.0f)
	{
		alpha[0] = 1.0f;
		speed *= -1;  // �A���t�@�l��1.0�𒴂����ꍇ�͔��]����
	}
	else if (alpha[0] < 0.0f)
	{
		alpha[0] = 0.0f;
		speed *= -1;  // �A���t�@�l��0.0����������ꍇ�����]����
	}
	spritedata->Signal->SetAlpha(alpha[0]);
	spritedata->spriteSPACE->SetAlpha(alpha[0]);
}

void EndScene::Draw()
{
}

void EndScene::Draw2D()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	//
	Sprite::PreDraw(cmdList);

	spritedata->spriteSceneChenge->Draw();
	Sprite::PostDraw();
}

void EndScene::FirstDraw2D()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	//
	Sprite::PreDraw(cmdList);
	spritedata->Signal->Draw();
	spritedata->spriteSPACE->Draw();
	Sprite::PostDraw();
}

void EndScene::DrawImGui()
{
}
