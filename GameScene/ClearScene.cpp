#include "ClearScene.h"
#include"GameObj/Player/Player.h"
#include"GameObj/Player/PlayerHead.h"
#include"SceneManager.h"
#include <base/SafeDelete.h>
#include"GameObj/Data/Data.h"
#include"GameObj/SpriteData/SpriteData.h"
void ClearScene::Initialize(DirectXCommon* dxCommon, Input* input, InputCamera* inputCamera, DebugText* text, PostEffect* post, SpriteManager* SpriteMan, Audio* audio)
{
	BaseScene::Initialize(dxCommon, input, inputCamera, text, post, SpriteMan, audio);
	
	data = new Data();
	data->SetStageCount(3);
	data->Initialize();
	
	spritedata = new SpriteData();
	spritedata->SetStageCount(3);
	spritedata->Initialize(SpriteMan);

	
	spritedata->spriteSceneChenge->SetSize({ 1280,720 });
	
	
	Object3d::SetCamera(inputCamera);
	// ライト生成
	light = Light::Create();
	// 3Dオブエクトにライトをセット
	Object3d::SetLightGroup(light);
	light->SetSpotLightActive(0, true);
	light->SetSpotLightActive(1, true);
	light->SetCircleShadowActive(0, true);
	light->SetCircleShadowActive(1, true);
	Object3d::SetLightGroup(light);
	
	data->objPlayerBody->SetPosition({ PBodyPosition });
	data->objPlayer->SetPlayer(data->objPlayerBody);
	data->objPlayer->SetPosition({ PBodyPosition });

	data->TitleMove[0]->SetPosition(TitlePosition[0]);
	data->TitleMove[0]->SetRotation({ 0,0,0 });	
	data->TitleMove[1]->SetRotation({ 0,180,0 });
	data->TitleMove[1]->SetPosition(TitlePosition[1]);
	
	data->Dome->SetPosition({ 180,0,0 });
	

	stage = new Stage();
	stage->Initialize();

	inputCamera->SetTarget(CameraPosition);
	inputCamera->SetDistance(3.0f);
	inputCamera->SetEye(XMFLOAT3(Eye));

	data->objPlayerBody->SetStartFlag(true);
	data->objPlayer->SetStartFlag(true);
	data->objPlayerBody->SetMoveFlags(true);
	data->objPlayer->SetMoveFlags(true);
	post->ResetTime();
}

void ClearScene::Finalize()
{
	safe_delete(light);
	data->Finalize();
}

void ClearScene::Update()
{

	if (SpriteX[0] > 0)
	{
		SpriteX[0] -= 12.8;
		SpriteY[0] -= 7.4;
	}
	PlayerPos[0] = PBodyPosition.x;
	PlayerPos[1] = PBodyPosition.y;
	PlayerPos[2] = PBodyPosition.z;


	CameraPosition.x = PBodyPosition.x;
	CameraPosition.y = PBodyPosition.y + 5;
	CameraPosition.z = PBodyPosition.z - 15;
	PBodyPosition = data->objPlayerBody->GetPosition();
	
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
	inputCamera->SetTarget(CameraPosition);
	inputCamera->SetEye(XMFLOAT3(Eye));
	inputCamera->Update();
	light->Update();
	inputCamera->SetTarget(CameraPosition);
	inputCamera->SetEye(XMFLOAT3(Eye));
	inputCamera->Update();
	data->objPlayerBody->Update(light);
	data->objPlayer->Update();

	data->Dome->Update();
	stage->Stage4();
	stage->GetCameraPos(CameraPosition);

	if (PBodyPosition.z > 35)
	{
		post->ClearTime();

	}
	if (PBodyPosition.z > 60)
	{
		float speed = 0.5;

		if (TitlePosition[0].x < 0.5)
		{
			TitlePosition[0].x += speed;
			TitlePosition[1].x -= speed;

		}
		else
		{
			EndFlag = true;

		}
	}

	if (EndFlag)
	{
		Time += 1;

		if (Time > 20)
		{
			TitlePosition[0].y += 1;
			TitlePosition[1].y += 1;
			PBodyPosition.y += 1;
			alpha[0] += 0.02;
		}
		data->objPlayerBody->SetPosition(PBodyPosition);
		data->objPlayer->SetPosition(PBodyPosition);

		if (alpha[0] > 1)
		{
			stage->StageChange();
			SceneManager::GetInstance()->ChangeScene("TITLE");
		}
	}

	data->TitleMove[0]->SetPosition({ TitlePosition[0] });
	data->TitleMove[1]->SetPosition({ TitlePosition[1] });
	data->TitleMove[0]->Update();
	data->TitleMove[1]->Update();
	spritedata->spriteSceneChenge->SetPosition({ 640 - SpriteX[0], 360 - SpriteY[0] });
	spritedata->spriteSceneChenge->SetSize({ SpriteX[0] * 2.0f, SpriteY[0] * 2.0f });
	spritedata->Black->SetAlpha(alpha[0]);

	PostTime[0] = post->Time;
}

void ClearScene::Draw()
{

	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	Object3d::PreDraw(cmdList);
	if (EndFlag == false)
	{
		data->objPlayerBody->Draw();
		data->objPlayer->Draw();
	}

	stage->StageObjDraw();
	data->Dome->Draw();
	data->TitleMove[0]->Draw();
	data->TitleMove[1]->Draw();
	Object3d::PostDraw();
}

void ClearScene::Draw2D()
{

	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	Sprite::PreDraw(cmdList);
	spritedata->spriteSceneChenge->Draw();
	Sprite::PostDraw();
}

void ClearScene::FirstDraw2D()
{

	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	Sprite::PreDraw(cmdList);
	spritedata->Black->Draw();
	Sprite::PostDraw();
}

void ClearScene::DrawImGui()
{
	ImGui::Begin("pos");
	ImGui::SetWindowPos(ImVec2(0, 0));
	ImGui::SetWindowSize(ImVec2(500, 200));
	ImGui::InputFloat3("PlayerPosition", PlayerPos);
	ImGui::InputFloat("time", PostTime);
	ImGui::End();
}