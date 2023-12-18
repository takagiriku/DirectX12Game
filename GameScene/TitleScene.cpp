#include "TitleScene.h"
#include"SceneManager.h"
#include <base/SafeDelete.h>
#include"GameObj/Player/Player.h"
#include"GameObj/Player/PlayerHead.h"
#include"GameObj/stage/stage.h"
#include"GameObj/key/Key.h"
#include"GameObj/Battery/Battery.h"
#include"GameObj/Data/Data.h"
#include"GameObj/SpriteData/SpriteData.h"

void TitleScene::Initialize(DirectXCommon* dxCommon, Input* input, InputCamera* inputCamera, DebugText* text, PostEffect* post, SpriteManager* SpriteMan, Audio* audio)
{

	BaseScene::Initialize(dxCommon, input, inputCamera, text, post, SpriteMan, audio);

	data = new Data();
	data->SetStageCount(0);
	data->Initialize();

	spritedata = new SpriteData();
	spritedata->SetStageCount(0);
	spritedata->Initialize(SpriteMan);
	
	particleMan = ParticleManager::Create(dxCommon->GetDevice(), inputCamera);
    Object3d::SetCamera(inputCamera);
  
	data->TitleMove[0]->SetRotation({ 0,0,0 });
	data->TitleMove[1]->SetRotation({ 0,180,0 });
	
	data->Keys[0]->SetPosition(KeyPosition);
	data->battery[0]->SetPosition(BatteryPosition);
 
	data->objPlayerBody->SetPosition(PBodyPosition);	
	data->objPlayer->SetPosition(PBodyPosition);
	
    stage = new Stage();
    stage->Initialize();
	
    inputCamera->SetTarget(CameraPosition);
    inputCamera->SetDistance(3.0f);
    inputCamera->SetEye(XMFLOAT3(Eye));
	
	post->SetStartFlag(false);
	post->ResetTime();
	
	audio->SoundStop("se_amc04.wav");
	audio->SoundLoadWave("digitalworld.wav");

}

void TitleScene::Finalize()
{
   safe_delete(particleMan);
   safe_delete(stage);
   data->Finalize();

}

void TitleScene::Update()
{
	audio->SoundPlayWave("digitalworld.wav", true);

	inputCamera->SetTarget(CameraPosition);
	inputCamera->SetEye(XMFLOAT3(Eye));
	inputCamera->Update();

	if (input->Trigger(DIK_SPACE))
	{
		data->objPlayerBody->SetStartFlag(true);
		data->objPlayer->SetStartFlag(true);
		StartFlag = true;
	}
	if(StartFlag)
	{
		data->TitleMove[0]->SetPosition({ 0,PBodyPosition.y,6 });
		data->TitleMove[1]->SetPosition({ 0,PBodyPosition.y,6 });
		if(PBodyPosition.y<45)
		CameraPosition.x = PBodyPosition.x;
		CameraPosition.y = PBodyPosition.y + 5;
		CameraPosition.z = PBodyPosition.z - 15;
	}
	else
	{
		PBodyPosition = { 0,55,-2 };
		CameraPosition.x = PBodyPosition.x;
		CameraPosition.y = PBodyPosition.y - 5;
		CameraPosition.z = PBodyPosition.z - 15;
		post->ResetTime();
	}

	PBodyPosition = data->objPlayerBody->GetPosition();
	

	if (data->battery[0]->BatFlag == false && PBodyPosition.z > -3 && PBodyPosition.y < 2)
	{//落下後動けるように
		data->TitleMove[0]->SetRotation({ 0,0,45 });
		data->TitleMove[1]->SetRotation({ 0,180,45 });
		if (a[0] < 0.3)
		{
			a[0] += 0.05;
		}	
		post->SetStartFlag(true);
	}
	if (data->Keys[0]->KeyFlag && abs(PBodyPosition.x - stage->Gole.x) <= 5&& PBodyPosition.z > 68)
	{//キーを取って動いたオブジェクトの座標に近づいたら
		data->objPlayerBody->SetMoveFlags(false);
		data->objPlayer->SetMoveFlags(false);
		if (SpriteX[0] < 1280) // SpriteXが画面の中心まで移動するまで
		{
			SpriteX[0] += 12.8;
			SpriteY[0] += 7.4;
		}
		if (SpriteX[0] > 1270)
		{
			stage->StageChange();
			post->ResetTime();
			SceneManager::GetInstance()->ChangeScene("NORMAL");
		}
	}
	spritedata->spriteSceneChenge->SetPosition({ 640 - SpriteX[0], 360 - SpriteY[0] });
	spritedata->spriteSceneChenge->SetSize({ SpriteX[0] * 2.0f, SpriteY[0] * 2.0f });
	
	if (post->Time > 160)
	{
		post->ResetTime();
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
	spritedata->spriteSPACE->SetAlpha(alpha[0]);
	
	particleMan->Update();
	
	stage->GetCameraPos(CameraPosition);
	stage->SetKeyFlag(data->Keys[0]->KeyFlag);
	stage->Stage0();
	data->Update(post,particleMan);
}

void TitleScene::Draw()
{
    // コマンドリストの取得
    ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	Object3d::PreDraw(cmdList);
	if (StartFlag == false)
	{
		for (int i = 0; i < 9; i++)
		{
			data->TitleObjs[i]->Draw();
		}
	}
	else
	{
		data->TitleMove[0]->Draw();
		data->TitleMove[1]->Draw();
	}
	if (StartFlag)
	{
		stage->StageObjDraw0();
		data->battery[0]->Draw();
		data->objPlayerBody->Draw();
		data->objPlayer->Draw();
		data->Keys[0]->Draw();
	}
	data->Dome->Draw();
	particleMan->Draw(cmdList);
	Object3d::PostDraw();
}

void TitleScene::Draw2D()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	Sprite::PreDraw(cmdList);
	spritedata->spriteSceneChenge->Draw();
	Sprite::PostDraw();
}
void TitleScene::FirstDraw2D()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	Sprite::PreDraw(cmdList);
	if (StartFlag == false)
	{
		spritedata->spriteSPACE->Draw();
		spritedata->TITLE->Draw();
	}
	Sprite::PostDraw();
}

void TitleScene::DrawImGui()
{
	ImGui::Begin("pos");
	ImGui::SetWindowPos(ImVec2(0, 0));
	ImGui::SetWindowSize(ImVec2(500, 200));
	ImGui::InputFloat3("Player", data->objPlayer->ppos);
	ImGui::End();
}
