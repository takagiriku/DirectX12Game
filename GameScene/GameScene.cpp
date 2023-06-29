#include "GameScene.h"
#include"GameObj/Player/Player.h"
#include"SceneManager.h"
#include <base/SafeDelete.h>



void GameScene::Initialize(DirectXCommon* dxCommon, Input* input, InputCamera* inputCamera, DebugText* text, PostEffect* post, SpriteManager* SpriteMan, Audio* audio)
{

	BaseScene::Initialize(dxCommon, input, inputCamera, text, post, SpriteMan, audio);

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
	mDome = Model::CreateOBJ("skydome");
	Dome = Object3d::Create(mDome);
	Dome->SetPosition({ 180,0,0 });
	Dome->SetRotation({ 0,0,0 });
	Dome->SetScale({ 3,3,3 });

	modelPlayerBody = Model::CreateOBJ("playerbody");
	modelPlayer = Model::CreateOBJ("playerobj");
	mKey = Model::CreateOBJ("key");
	mBattery = Model::CreateOBJ("battery");

	objPlayerBody = Player::Create(modelPlayerBody);
	objPlayer = Player::Create(modelPlayer);
	
	objPlayerBody->SetScale({ 1.5,1.5,1.5 });
	objPlayer->SetScale({ 1.5,1.5,1.5 });
	for (int i = 0; i < 10; i++)
	{
		Battery[i] = Battery::Create(mBattery);
		Battery[i]->SetScale({1.5,1.5,1.5});
		Battery[i]->SetPosition(BatteryPosition[i]);
	}
	
	Key = Key::Create(mKey);
	Key->SetScale({ 5,5,5 });
	Key->SetPosition(KeyPosition);

	stage = new Stage();
	stage->Initialize();

	inputCamera->SetTarget(CameraPosition);
	inputCamera->SetDistance(3.0f);
	inputCamera->SetEye(XMFLOAT3(Eye));

	
	objPlayerBody->SetStartFlag(true);
	objPlayer->SetStartFlag(true);
	post->SetStartFlag(true);

	objPlayerBody->SetMoveFlags(true);
	objPlayer->SetMoveFlags(true);
}


void GameScene::Finalize()
{
	safe_delete(spriteSceneChenge);
	safe_delete(Dome);
	safe_delete(particleMan);
	safe_delete(mDome);
	safe_delete(mKey);
	safe_delete(mBattery);
	safe_delete(light);
	safe_delete(stage);
	safe_delete(objPlayerBody);
	safe_delete(objPlayer);
	safe_delete(modelPlayerBody);
	safe_delete(modelPlayer);
	safe_delete(Key);
	for (int i = 0; i < 10; i++) {
		safe_delete(Battery[i]);
	}
	
}

void GameScene::Update()
{
	if (Key->KeyFlag == false)
	{
		if (SpriteX[0] > 0)
		{
			SpriteX[0] -= 12.8;
			SpriteY[0] -= 7.4;
		}
	}
	
	

	PBodyPosition = objPlayerBody->GetPosition();
	if (objPlayerBody->MoveCount == 1)
		//プレイヤーの処理
	{
		if (input->Push(DIK_A) || input->Push(DIK_D))
		{
			if (input->Push(DIK_D))
			{//ラグの問題でxに+1する
				//BodyとHeadの回転
				objPlayer->SetRotation({ 0,90,0 });
				PlayerBodyRotz -= 5;
				PlayerBodyRotx = 0;

			}
			if (input->Push(DIK_A))
			{//ラグの問題でxに-1する
				//Bodyの回転
				objPlayer->SetRotation({ 0,270,0 });
				PlayerBodyRotz += 5;
				PlayerBodyRotx = 0;
			
			}
			
		}
		else if (input->Push(DIK_S) || input->Push(DIK_W))
		{
			if (input->Push(DIK_W))
			{//ラグの問題でzに+1する
				//BodyとHeadの回転
				objPlayer->SetRotation({ 0,0,0 });
				PlayerBodyRotx += 5;
				PlayerBodyRotz = 90;


			}
			if (input->Push(DIK_S))
			{//ラグの問題でzに-1する
				//BodyとHeadの回転
				objPlayer->SetRotation({ 0,180,0 });
				PlayerBodyRotz = 90;
				PlayerBodyRotx -= 5;

				
			}
			
		}


	}
	

	CameraPosition.x = PBodyPosition.x;
	CameraPosition.y = PBodyPosition.y + 5;
	CameraPosition.z = PBodyPosition.z - 15;

	PlayerPos[0] = PBodyPosition.x;
	PlayerPos[1] = PBodyPosition.y;
	PlayerPos[2] = PBodyPosition.z;

	CameraPos[0] = CameraPosition.x;
	CameraPos[1] = CameraPosition.y;
	CameraPos[2] = CameraPosition.z;

	KeyPos[0] = KeyPosition.x;
	KeyPos[1] = KeyPosition.y;
	KeyPos[2] = KeyPosition.z;

	//BatPos[0] = BatteryPosition.x;
	//BatPos[1] = BatteryPosition.y;
	//BatPos[2] = BatteryPosition.z;

	inputCamera->SetTarget(CameraPosition);
	inputCamera->SetEye(XMFLOAT3(Eye));
	inputCamera->Update();
	
	objPlayerBody->SetRotation({ PlayerBodyRotx,PlayerBodyRoty,PlayerBodyRotz });
	Dome->Update();
	light->Update();
	
	for (int i = 0; i < 10; i++)
	{
		Battery[i]->Update(particleMan, post, light,i+2);
		Battery[i]->SetPos(PBodyPosition);
		Battery[i]->SetPosition(BatteryPosition[i]);
	}
	Key->SetPosition(KeyPosition);
	Key->Update(particleMan, light);
	Key->SetPos(PBodyPosition);
	particleMan->Update();
	objPlayerBody->Update(light);
	objPlayer->Update(light);

	stage->Stage1();
	stage->GetCameraPos(CameraPosition);
	if (Key->KeyFlag)
	{
		stage->SetKeyFlag(Key->KeyFlag);
	}
	float Gole = 22;
	if (Key->KeyFlag && abs(PBodyPosition.x - Gole) <= 5 && PBodyPosition.y > 10 && PBodyPosition.z > 73)
	{
		objPlayerBody->SetMoveFlags(false);
		objPlayer->SetMoveFlags(false);
		if (SpriteX[0] < 1280) // SpriteXが画面の中心まで移動するまで
		{
			SpriteX[0] += 12.8;
			SpriteY[0] += 7.4;
		}
		if (SpriteX[0] > 1270)
		{
			stage->StageChange();
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
	objPlayerBody->Draw();
	objPlayer->Draw();
	Key->Draw();
	for (int i = 0; i < 10; i++)
	{
		Battery[i]->Draw();
	}
	
	stage->StageObjDraw();
	Dome->Draw();
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
	ImGui::InputFloat3("PlayerPosition", PlayerPos);
	ImGui::InputFloat3("CameraPosition", CameraPos);
	ImGui::InputFloat("al", alpha);
	ImGui::InputFloat("time", Time);
	ImGui::End();
}
