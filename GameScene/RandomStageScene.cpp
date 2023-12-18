#include "RandomStageScene.h"
#include"GameObj/Player/Player.h"
#include"GameObj/Player/PlayerHead.h"
#include"GameObj/BlockObj//BlockObj.h"
#include"SceneManager.h"
#include <base/SafeDelete.h>
#include"GameObj/Data/Data.h"
#include"GameObj/SpriteData/SpriteData.h"
void RandomStageScene::Initialize(DirectXCommon* dxCommon, Input* input, InputCamera* inputCamera, DebugText* text, PostEffect* post, SpriteManager* SpriteMan, Audio* audio)
{

	BaseScene::Initialize(dxCommon, input, inputCamera, text, post, SpriteMan, audio);
	data = new Data();
	data->SetStageCount(2);
	data->Initialize();

	spritedata = new SpriteData();
	spritedata->SetStageCount(2);
	spritedata->Initialize(SpriteMan);
	
	particleMan = ParticleManager::Create(dxCommon->GetDevice(), inputCamera);
	Object3d::SetCamera(inputCamera);
	
	for (int i = 0; i < 4; i++)
	{
		data->battery[i]->SetPosition(BatteryPosition[i]);
	}

	stage = new Stage();
	stage->Initialize();

	inputCamera->SetTarget(CameraPosition);
	inputCamera->SetDistance(3.0f);
	inputCamera->SetEye(XMFLOAT3(Eye));

	data->objPlayerBody->SetStartFlag(true);
	data->objPlayer->SetStartFlag(true);
	post->SetStartFlag(true);
	post->ResetTime();	
}


void RandomStageScene::Finalize()
{
	safe_delete(particleMan);
	safe_delete(light);
	safe_delete(stage);
	data->Finalize();
}

void RandomStageScene::Update()
{
	PBodyPosition = data->objPlayerBody->GetPosition();

	CameraPosition.x = PBodyPosition.x;
	CameraPosition.y = PBodyPosition.y + 5;
	CameraPosition.z = PBodyPosition.z - 15;

	inputCamera->SetTarget(CameraPosition);
	inputCamera->SetEye(XMFLOAT3(Eye));
	inputCamera->Update();

	stage->Stage3();
	stage->GetCameraPos(CameraPosition);
	stage->SetKeyFlag(data->Keys[0]->KeyFlag);

	for (int i = 0; i < 10; i++)
	{
		data->objblock[i]->SetTilePos(stage->TilePosition);
	}
	data->Keys[0]->SetTilePos(stage->TilePosition3);
		
	if (data->Keys[0]->KeyFlag && abs(PBodyPosition.x - stage->Gole.x) <= 5 && PBodyPosition.z > 73)
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
			SceneManager::GetInstance()->ChangeScene("CLEAR");
		}
	}
	else
	{
		if (SpriteX[0] > 0)
		{
			SpriteX[0] -= 12.8;
			SpriteY[0] -= 7.4;
		}
	}
	Time[0] = post->Time;

	float speed = 0.005;
	if (post->Time > 170)
	{
		AlphaFlag = true;
	}
	else
	{
		AlphaFlag = false;
	}
	if (AlphaFlag)
	{
		if (alpha[0] < 1)
		{
			alpha[0] += speed;
		}

	}
	if (AlphaFlag == false)
	{
		if (alpha[0] > 0.005)
		{
			alpha[0] -= speed;
		}
	}
	if (alpha[0] > 1)
	{
		stage->StageChange();
		post->ResetTime();
		SceneManager::GetInstance()->ChangeScene("END");
	}

	spritedata->Black->SetAlpha(alpha[0]);
	spritedata->spriteSceneChenge->SetPosition({ 640 - SpriteX[0], 360 - SpriteY[0] });
	spritedata->spriteSceneChenge->SetSize({ SpriteX[0] * 2.0f, SpriteY[0] * 2.0f });
	
	
	particleMan->Update();
	data->Update(post, particleMan);

}

void RandomStageScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	Object3d::PreDraw(cmdList);
	data->objPlayerBody->Draw();
	data->objPlayer->Draw();
	data->Keys[0]->Draw();
	
	for (int i = 0; i < 4; i++)
	{
		data->battery[i]->Draw();
	}
	for (int i = 0; i < 10; i++)
	{
		data->objblock[i]->Draw();
	}
	stage->StageObjDraw();
	data->Dome->Draw();
	particleMan->Draw(cmdList);
	Object3d::PostDraw();

}

void RandomStageScene::Draw2D()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	Sprite::PreDraw(cmdList);
	spritedata->spriteSceneChenge->Draw();
	Sprite::PostDraw();
}

void RandomStageScene::FirstDraw2D()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	Sprite::PreDraw(cmdList);
	spritedata->Black->Draw();
	Sprite::PostDraw();
}

void RandomStageScene::DrawImGui()
{
	ImGui::Begin("pos");
	ImGui::SetWindowPos(ImVec2(0, 0));
	ImGui::SetWindowSize(ImVec2(500, 200));
	ImGui::InputFloat("al", alpha);
	ImGui::InputFloat("time", Time);
	ImGui::InputFloat3("Player", data->objPlayer->ppos);
	ImGui::End();
}