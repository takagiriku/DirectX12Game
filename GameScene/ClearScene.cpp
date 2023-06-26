#include "ClearScene.h"
#include"GameObj/Player/Player.h"
#include"SceneManager.h"
#include <base/SafeDelete.h>

void ClearScene::Initialize(DirectXCommon* dxCommon, Input* input, InputCamera* inputCamera, DebugText* text, PostEffect* post, SpriteManager* SpriteMan, Audio* audio)
{
	BaseScene::Initialize(dxCommon, input, inputCamera, text, post, SpriteMan, audio);

	SpriteMan->LoadTexture(0, L"Resources/scenechenge.png");
	SpriteMan->LoadTexture(1, L"Resources/Black.png");
	
	spriteSceneChenge = new Sprite;
	spriteSceneChenge->Create(0);
	
	Black = new Sprite;
	Black->Create(1);
	
	
	
	spriteSceneChenge->SetSize({ 1280,720 });
	
	
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
	modelPlayerBody = Model::CreateOBJ("playerbody");
	modelPlayer = Model::CreateOBJ("playerobj");
	objPlayerBody = Player::Create(modelPlayerBody);
	objPlayerBody->SetScale({ 1.5,1.5,1.5 });
	objPlayerBody->SetPosition({ PBodyPosition });
	objPlayer = Player::Create(modelPlayer);
	objPlayer->SetScale({ 1.5,1.5,1.5 });
	objPlayer->SetPosition({ PBodyPosition });

	mTitleMove = Model::CreateOBJ("titleobj");
	TitleMove[0] = Object3d::Create(mTitleMove);
	TitleMove[0]->SetPosition(TitlePosition[0]);
	TitleMove[0]->SetScale({ 1.5,1.5,1.5 });
	TitleMove[0]->SetRotation({ 0,0,0 });
	;

	TitleMove[1] = Object3d::Create(mTitleMove);
	TitleMove[1]->SetRotation({ 0,180,0 });
	TitleMove[1]->SetPosition(TitlePosition[1]);
	TitleMove[1]->SetScale({ 1.5,1.5,1.5 });

	mDome = Model::CreateOBJ("skydome");
	Dome = Object3d::Create(mDome);
	Dome->SetPosition({ 180,0,0 });
	Dome->SetRotation({ 0,0,0 });
	Dome->SetScale({ 3,3,3 });

	stage = new Stage();
	stage->Initialize();

	inputCamera->SetTarget(CameraPosition);
	inputCamera->SetDistance(3.0f);
	inputCamera->SetEye(XMFLOAT3(Eye));

	objPlayerBody->SetStartFlag(true);
	objPlayer->SetStartFlag(true);
	objPlayerBody->SetMoveFlags(true);
	objPlayer->SetMoveFlags(true);
}

void ClearScene::Finalize()
{
	safe_delete(spriteSceneChenge);
	safe_delete(Dome);
	safe_delete(mDome);
	safe_delete(light);
	safe_delete(objPlayerBody);
	safe_delete(objPlayer);
	safe_delete(modelPlayerBody);
	safe_delete(modelPlayer);
	safe_delete(mTitleMove);
	safe_delete(TitleMove[0]);
	safe_delete(TitleMove[1]);
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
	
	
	inputCamera->SetTarget(CameraPosition);
	inputCamera->SetEye(XMFLOAT3(Eye));
	inputCamera->Update();
	objPlayerBody->SetRotation({ PlayerBodyRotx,PlayerBodyRoty,PlayerBodyRotz });
	light->Update();
	inputCamera->SetTarget(CameraPosition);
	inputCamera->SetEye(XMFLOAT3(Eye));
	inputCamera->Update();
	objPlayerBody->Update(light);
	objPlayer->Update(light);

	Dome->Update();
	stage->Stage4();
	stage->GetCameraPos(CameraPosition);

	if (PBodyPosition.z > 35)
	{
		post->SetStartFlag(false);

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
		objPlayerBody->SetPosition(PBodyPosition);
		objPlayer->SetPosition(PBodyPosition);

		if (alpha[0] > 1)
		{
			stage->StageChange();
			SceneManager::GetInstance()->ChangeScene("TITLE");
		}
	}

	TitleMove[0]->SetPosition({ TitlePosition[0] });
	TitleMove[1]->SetPosition({ TitlePosition[1] });
	TitleMove[0]->Update();
	TitleMove[1]->Update();
	spriteSceneChenge->SetPosition({ 640 - SpriteX[0], 360 - SpriteY[0] });
	spriteSceneChenge->SetSize({ SpriteX[0] * 2.0f, SpriteY[0] * 2.0f });
	Black->SetAlpha(alpha[0]);

	test[0] = post->Time;
}

void ClearScene::Draw()
{

	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	Object3d::PreDraw(cmdList);
	if (EndFlag == false)
	{
		objPlayerBody->Draw();
		objPlayer->Draw();
	}

	stage->StageObjDraw();
	Dome->Draw();
	TitleMove[0]->Draw();
	TitleMove[1]->Draw();
	Object3d::PostDraw();
}

void ClearScene::Draw2D()
{

	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	Sprite::PreDraw(cmdList);
	spriteSceneChenge->Draw();
	Sprite::PostDraw();
}

void ClearScene::FirstDraw2D()
{

	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	Sprite::PreDraw(cmdList);
	Black->Draw();
	Sprite::PostDraw();
}

void ClearScene::DrawImGui()
{
	ImGui::Begin("pos");
	ImGui::SetWindowPos(ImVec2(0, 0));
	ImGui::SetWindowSize(ImVec2(500, 200));
	ImGui::InputFloat3("PlayerPosition", PlayerPos);
	ImGui::InputFloat("time", test);
	ImGui::End();
}