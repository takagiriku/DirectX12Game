#include "GameScene.h"
#include"GameObj/Player/Player.h"
#include"GameObj/Player/PlayerHead.h"
#include"SceneManager.h"
#include <base/SafeDelete.h>
#include"Data.h"


void GameScene::Initialize(DirectXCommon* dxCommon, Input* input, InputCamera* inputCamera, DebugText* text, PostEffect* post, SpriteManager* SpriteMan, Audio* audio)
{

	BaseScene::Initialize(dxCommon, input, inputCamera, text, post, SpriteMan, audio);
	data = new Data();
	data->SetStageCount(1);
	data->Initialize();

	SpriteMan->LoadTexture(0, L"Resources/scenechenge.png");
	spriteSceneChenge = new Sprite();
	spriteSceneChenge->Create(0);
	
	SpriteMan->LoadTexture(3, L"Resources/black.png");
	Black = new Sprite();
	Black->Create(3);
	
	particleMan = ParticleManager::Create(dxCommon->GetDevice(), inputCamera);
	Object3d::SetCamera(inputCamera);
	// ライト生成
	light = Light::Create();
	// 3Dオブエクトにライトをセット
	Object3d::SetLightGroup(light);
	light->SetSpotLightActive(0, true);
	light->SetSpotLightActive(1, true);
	

	
	light->SetCircleShadowActive(0, true);
	light->SetCircleShadowActive(1, true);
	for (int i = 2; i < 11; i++)
	{
		light->SetPointLightActive(i, true);
		light->SetCircleShadowActive(i, true);
	}
	

	Object3d::SetLightGroup(light);
	data->Dome->SetPosition({ 180,0,0 });
	data->Dome->SetRotation({ 0,0,0 });
	data->Dome->SetScale({ 3,3,3 });

	data->objPlayer->SetPlayer(data->objPlayerBody);
	
	data->objPlayerBody->SetScale({ 1.5,1.5,1.5 });
	data->objPlayer->SetScale({ 1.5,1.5,1.5 });
	for (int i = 0; i < 8; i++)
	{
		data->battery[i]->SetScale({1.5,1.5,1.5});
		data->battery[i]->SetPosition(BatteryPosition[i]);
	}
	
	
	data->Keys[0]->SetScale({5,5,5});
	data->Keys[0]->SetPosition(KeyPosition);

	stage = new Stage();
	stage->Initialize();

	inputCamera->SetTarget(CameraPosition);
	inputCamera->SetDistance(3.0f);
	inputCamera->SetEye(XMFLOAT3(Eye));

	
	data->objPlayerBody->SetStartFlag(true);
	data->objPlayer->SetStartFlag(true);
	post->SetStartFlag(true);
	post->ResetTime();
	data->objPlayerBody->SetMoveFlags(true);
	data->objPlayer->SetMoveFlags(true);
}


void GameScene::Finalize()
{
	safe_delete(spriteSceneChenge);
	safe_delete(particleMan);
	safe_delete(light);
	safe_delete(stage);
	data->Finalize();
}

void GameScene::Update()
{
	if (data->Keys[0]->KeyFlag == false)
	{
		if (SpriteX[0] > 0)
		{
			SpriteX[0] -= 12.8;
			SpriteY[0] -= 7.4;
		}
	}
	
	

	PBodyPosition = data->objPlayerBody->GetPosition();
	
	CameraPosition.x = PBodyPosition.x;
	CameraPosition.y = PBodyPosition.y + 5;
	CameraPosition.z = PBodyPosition.z - 15;

	inputCamera->SetTarget(CameraPosition);
	inputCamera->SetEye(XMFLOAT3(Eye));
	inputCamera->Update();
	
	
	data->Dome->Update();
	light->Update();
	
	for (int i = 0; i < 8; i++)
	{
		data->battery[i]->Update(particleMan, post, light,i+2);
		data->battery[i]->SetPos(PBodyPosition);
		data->battery[i]->SetPosition(BatteryPosition[i]);
	}
	data->Keys[0]->SetPosition(KeyPosition);
	data->Keys[0]->Update(particleMan, light);
	data->Keys[0]->SetPos(PBodyPosition);
	particleMan->Update();
	data->objPlayerBody->Update(light);
	data->objPlayer->Update();

	stage->Stage1();
	stage->GetCameraPos(CameraPosition);
	if (data->Keys[0]->KeyFlag)
	{
		stage->SetKeyFlag(data->Keys[0]->KeyFlag);
	}
	
	if (data->Keys[0]->KeyFlag && abs(PBodyPosition.x - stage->Gole.x) <= 5 && PBodyPosition.y > 10 && PBodyPosition.z > 73)
	{
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
			SceneManager::GetInstance()->ChangeScene("GAME2");
		}
	}
	Time[0] = post->Time;
	
	float speed = 0.005;
	if (post->Time >170)
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
	
	Black->SetAlpha(alpha[0]);
	spriteSceneChenge->SetPosition({ 640 - SpriteX[0], 360 - SpriteY[0] });
	spriteSceneChenge->SetSize({ SpriteX[0] * 2.0f, SpriteY[0] * 2.0f });

}

void GameScene::Draw()
{
	
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	Object3d::PreDraw(cmdList);
	data->objPlayerBody->Draw();
	data->objPlayer->Draw();
	data->Keys[0]->Draw();
	for (int i = 0; i < 8; i++)
	{
		data->battery[i]->Draw();
	}
	
	stage->StageObjDraw();
	data->Dome->Draw();
	particleMan->Draw(cmdList);
	Object3d::PostDraw();


}

void GameScene::Draw2D()
{
	
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	Sprite::PreDraw(cmdList);
	spriteSceneChenge->Draw();
	Sprite::PostDraw();
}

void GameScene::FirstDraw2D()
{

	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	Sprite::PreDraw(cmdList);
	Black->Draw();
	Sprite::PostDraw();
}

void GameScene::DrawImGui()
{
	ImGui::Begin("pos");
	ImGui::SetWindowPos(ImVec2(0, 0));
	ImGui::SetWindowSize(ImVec2(500, 200));
	ImGui::InputFloat("al", alpha);
	ImGui::InputFloat("time", Time);
	ImGui::InputFloat3("Player", data->objPlayer->ppos);
	ImGui::End();
}
