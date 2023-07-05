#include "GameScene2.h"
#include"GameObj/Player/Player.h"
#include"SceneManager.h"
#include <base/SafeDelete.h>


void GameScene2::Initialize(DirectXCommon* dxCommon, Input* input, InputCamera* inputCamera, DebugText* text, PostEffect* post, SpriteManager* SpriteMan, Audio* audio)
{

	BaseScene::Initialize(dxCommon, input, inputCamera, text, post, SpriteMan, audio);

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
	mDome = Model::CreateOBJ("skydome");
	modelPlayerBody = Model::CreateOBJ("playerbody");
	modelPlayer = Model::CreateOBJ("playerobj");
	mKey = Model::CreateOBJ("key");
	mBattery = Model::CreateOBJ("battery");
	mBox = Model::CreateOBJ("Box");
	mBBox = Model::CreateOBJ("blackBox");
	
	mTile = Model::CreateOBJ("Gole");

	objPlayerBody = Player::Create(modelPlayerBody);
	objPlayerBody->SetScale({ 1.5,1.5,1.5 });
	objPlayerBody->SetPosition({ PBodyPosition });
	objPlayer = Player::Create(modelPlayer);
	objPlayer->SetScale({ 1.5,1.5,1.5 });
	objPlayer->SetPosition({ PBodyPosition });

	Dome = Object3d::Create(mDome);
	Dome->SetPosition({ 180,0,0 });
	Dome->SetRotation({ 0,0,0 });
	Dome->SetScale({ 3,3,3 });
	for (int i = 0; i < 4; i++)
	{
		Battery[i] = Battery::Create(mBattery);
		Battery[i]->SetScale({ 1.5,1.5,1.5 });
		Battery[i]->SetPosition(BatteryPosition[i]);
		Box[i] = Box::Create(mBox);
		Box[i]->SetPosition(BoxPosition[i]);
		BBox[i] = Object3d::Create(mBBox);
		BBox[i]->SetPosition(BBoxPosition[i]);
	}
	for (int i = 0; i < 8; i++)
	{
		Tile[i] = Tile::Create(mTile);
		Tile[i]->SetPosition(TilePosition[i]);
		Tile[i]->SetScale({ 1.1,1.1,1.1 });
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
	post->ResetTime();
	post->SetStartFlag(true);
	objPlayerBody->SetMoveFlags(true);
	objPlayer->SetMoveFlags(true);
}


void GameScene2::Finalize()
{
	safe_delete(spriteSceneChenge);
	safe_delete(Dome);
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
	for (int i = 0; i < 4; i++) {
		safe_delete(Box[i]);
		safe_delete(BBox[i]);
		safe_delete(Battery[i]);
	}
	for (int i = 0; i < 8; i++) {
		safe_delete(Tile[i]);
	}
}

void GameScene2::Update()
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

	BatPos[0] = BoxPosition[0].x;
	BatPos[1] = BoxPosition[0].y;
	BatPos[2] = BoxPosition[0].z;


	objPlayerBody->SetRotation({ PlayerBodyRotx,PlayerBodyRoty,PlayerBodyRotz });
	Dome->Update();
	light->Update();

	for (int i = 0; i < 4; i++)
	{
		Battery[i]->Update(particleMan, post, light,i+2);
		Battery[i]->SetPos(PBodyPosition);
		//Battery[i]->SetPosition(BatteryPosition[i]);
		Box[i]->Update();
		Box[i]->SetPos(PBodyPosition);
		//Box[i]->SetPosition(BoxPosition[i]);
		BBox[i]->Update();
	}
	
	for (int i = 0; i < 8; i++)
	{
		Tile[i]->Update(i);
		Tile[i]->SetPos(PBodyPosition);
		
	}

	Key->SetPosition(KeyPosition);
	Key->Update(particleMan, light);
	Key->SetPos(PBodyPosition);

	objPlayerBody->Update(light);
	objPlayer->Update(light);

	test = Tile[0]->GetPosition();

	tests[0] = test.x;
	tests[1] = test.y;
	tests[2] = test.z;

	if (Key->KeyFlag)
	{
		Time += 1;
		if (Time < 150)
		{
			
			CameraPosition.x = 62;
			CameraPosition.y = 16;
			CameraPosition.z = 58;
			objPlayerBody->SetMoveFlags(false);
			objPlayer->SetMoveFlags(false);
		}
		else
		{
			objPlayerBody->SetMoveFlags(true);
			objPlayer->SetMoveFlags(true);
		}
		stage->SetKeyFlag(Key->KeyFlag);
	}
	

	for (int i = 0; i < 4; i++)
	{
		if (Battery[i]->BatFlag)
		{
			AlphaFlag = false;
			
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (Box[i]->GetBoxFlag())
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
				objPlayerBody->SetStartFlag(false);
				objPlayer->SetStartFlag(false);
			}
			else
			{
				objPlayerBody->SetStartFlag(true);
				objPlayer->SetStartFlag(true);
			}
			
		}
	}
	stage->Stage3();
	stage->GetCameraPos(CameraPosition);
	if (FlagCount[0] == 1 && FlagCount[1] == 1 && FlagCount[2] == 1 && FlagCount[3] == 1)
	{
		Key->SetKeyFlag(true);
	}
	float Gole = 56;
	if (Key->KeyFlag && abs(PBodyPosition.x - Gole) <= 10&& PBodyPosition.z > 73)
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
	objPlayerBody->Draw();
	objPlayer->Draw();
	Key->Draw();
	for (int i = 0; i < 4; i++)
	{
		Battery[i]->Draw();
		Box[i]->Draw();
		BBox[i]->Draw();
	}
	for (int i = 0; i < 8; i++) {
		Tile[i]->Draw();
	}
	stage->StageObjDraw2();
	Dome->Draw();
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
	ImGui::InputFloat3("PlayerPosition", PlayerPos);
	ImGui::InputFloat3("CameraPosition", CameraPos);
	ImGui::InputFloat("al", alpha);
	ImGui::InputFloat3("Box", BatPos);
	ImGui::InputFloat3("Ttest", tests);
	ImGui::End();
}
