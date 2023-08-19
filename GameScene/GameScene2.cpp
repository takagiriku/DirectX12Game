#include "GameScene2.h"
#include"GameObj/Player/Player.h"
#include"GameObj/Player/PlayerHead.h"
#include"SceneManager.h"
#include <base/SafeDelete.h>
#include"Data.h"

void GameScene2::Initialize(DirectXCommon* dxCommon, Input* input, InputCamera* inputCamera, DebugText* text, PostEffect* post, SpriteManager* SpriteMan, Audio* audio)
{

	BaseScene::Initialize(dxCommon, input, inputCamera, text, post, SpriteMan, audio);
	data = new Data();
	data->SetStageCount(2);
	data->Initialize();
	SpriteMan->LoadTexture(0, L"Resources/scenechenge.png");
	spriteSceneChenge = new Sprite();
	spriteSceneChenge->Create(0);
	
	SpriteMan->LoadTexture(1, L"Resources/Black.png");
	Black = new Sprite();
	Black->Create(1);
	particleMan = ParticleManager::Create(dxCommon->GetDevice(), inputCamera);
	SpriteMan->LoadTexture(3, L"Resources/black.png");
	//Black->Create(3, { 0,0 });
	Object3d::SetCamera(inputCamera);
	// ライト生成
	light = Light::Create();
	// 3Dオブエクトにライトをセット
	Object3d::SetLightGroup(light);
	light->SetSpotLightActive(0, true);
	light->SetPointLightActive(0, true);
	
	
	
	light->SetCircleShadowActive(0, true);
	light->SetCircleShadowActive(1, true);

	for (int i = 2; i < 5; i++)
	{
		light->SetPointLightActive(i, true);
		light->SetCircleShadowActive(i, true);
	}
	Object3d::SetLightGroup(light);
	data->objPlayerBody->SetScale({ 1.5,1.5,1.5 });
	data->objPlayerBody->SetPosition({ PBodyPosition });
	
	data->objPlayer->SetPlayer(data->objPlayerBody);
	data->objPlayer->SetScale({ 1.5,1.5,1.5 });
	data->objPlayer->SetPosition({ PBodyPosition });

	data->Dome->SetPosition({ 180,0,0 });
	data->Dome->SetRotation({ 0,0,0 });
	data->Dome->SetScale({ 3,3,3 });
	for (int i = 0; i < 4; i++)
	{
		data->battery[i]->SetScale({ 1.5,1.5,1.5 });
		data->battery[i]->SetPosition(BatteryPosition[i]);
		
		data->Box[i]->SetPosition(BoxPosition[i]);
		data->BBox[i]->SetPosition(BBoxPosition[i]);
	}
	for (int i = 0; i < 8; i++)
	{
		data->Tile[i]->SetPosition(TilePosition[i]);
		data->Tile[i]->SetScale({ 1.1,1.1,1.1 });
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
	post->ResetTime();
	post->SetStartFlag(true);
	data->objPlayerBody->SetMoveFlags(true);
	data->objPlayer->SetMoveFlags(true);
}


void GameScene2::Finalize()
{
	safe_delete(spriteSceneChenge);
	safe_delete(light);
	safe_delete(stage);
	data->Finalize();
}

void GameScene2::Update()
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

	data->Dome->Update();
	light->Update();

	for (int i = 0; i < 4; i++)
	{
		data->battery[i]->Update(particleMan, post, light,i+2);
		data->battery[i]->SetPos(PBodyPosition);
		data->Box[i]->Update();
		data->Box[i]->SetPos(PBodyPosition);
		data->BBox[i]->Update();
	}
	
	for (int i = 0; i < 8; i++)
	{
		data->Tile[i]->Update(i);
		data->Tile[i]->SetPos(PBodyPosition);
		
	}

	data->Keys[0]->SetPosition(KeyPosition);
	data->Keys[0]->Update(particleMan, light);
	data->Keys[0]->SetPos(PBodyPosition);

	data->objPlayerBody->Update(light);
	data->objPlayer->Update();

	test = data->Tile[0]->GetPosition();

	tests[0] = test.x;
	tests[1] = test.y;
	tests[2] = test.z;

	if (data->Keys[0]->KeyFlag)
	{
		Time += 1;
		if (Time < 150)
		{
			
			CameraPosition.x = 62;
			CameraPosition.y = 16;
			CameraPosition.z = 58;
			data->objPlayerBody->SetMoveFlags(false);
			data->objPlayer->SetMoveFlags(false);
		}
		else
		{
			data->objPlayerBody->SetMoveFlags(true);
			data->objPlayer->SetMoveFlags(true);
		}
		stage->SetKeyFlag(data->Keys[0]->KeyFlag);
	}
	

	for (int i = 0; i < 4; i++)
	{
		if (data->battery[i]->BatFlag)
		{
			AlphaFlag = false;
			
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (data->Box[i]->GetBoxFlag())
		{
			if (FlagCount[i] == 0) {
				FlagCount[i] = 1;
				stage->BoxCount++;
				Time = 0;
			}
			Time += 1;

			if (Time < 125)
			{
				CameraPosition.x = 62;
				CameraPosition.y = 16;
				CameraPosition.z = 58;
				data->objPlayerBody->SetStartFlag(false);
				data->objPlayer->SetStartFlag(false);
			}
			else
			{
				data->objPlayerBody->SetStartFlag(true);
				data->objPlayer->SetStartFlag(true);
			}
			
		}
	}
	stage->Stage3();
	stage->GetCameraPos(CameraPosition);
	if (FlagCount[0] == 1 && FlagCount[1] == 1 && FlagCount[2] == 1 && FlagCount[3] == 1)
	{
		data->Keys[0]->SetKeyFlag(true);
	}
	float Gole = 61;
	if (data->Keys[0]->KeyFlag && abs(PBodyPosition.x - stage->Gole.x) <= 4 && PBodyPosition.z > 73)
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
			SceneManager::GetInstance()->ChangeScene("CLEAR");
		}
	}
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

	Black->SetAlpha(alpha[0]);
	spriteSceneChenge->SetPosition({ 640 - SpriteX[0], 360 - SpriteY[0] });
	spriteSceneChenge->SetSize({ SpriteX[0] * 2.0f, SpriteY[0] * 2.0f });
	particleMan->Update();
	inputCamera->SetTarget(CameraPosition);
	inputCamera->SetEye(XMFLOAT3(Eye));
	inputCamera->Update();
}

void GameScene2::Draw()
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
		data->Box[i]->Draw();
		data->BBox[i]->Draw();
	}
	for (int i = 0; i < 8; i++) {
		data->Tile[i]->Draw();
	}
	stage->StageObjDraw2();
	data->Dome->Draw();
	particleMan->Draw(cmdList);
	Object3d::PostDraw();


}

void GameScene2::Draw2D()
{

	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	Sprite::PreDraw(cmdList);
	spriteSceneChenge->Draw();
	Sprite::PostDraw();
}

void GameScene2::FirstDraw2D()
{

	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	Sprite::PreDraw(cmdList);
	Black->Draw();
	Sprite::PostDraw();
}

void GameScene2::DrawImGui()
{
	ImGui::Begin("pos");
	ImGui::SetWindowPos(ImVec2(0, 0));
	ImGui::SetWindowSize(ImVec2(500, 200));
	ImGui::InputFloat("al", alpha);
	ImGui::InputFloat3("Box", BatPos);
	ImGui::InputFloat3("Ttest", tests);
	ImGui::End();
}
