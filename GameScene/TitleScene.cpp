#include "TitleScene.h"
#include"SceneManager.h"
#include <base/SafeDelete.h>
#include"GameObj/Player/Player.h"
#include"GameObj/stage/stage.h"
#include"GameObj/key/Key.h"
#include"GameObj/Battery/Battery.h"
void TitleScene::Initialize(DirectXCommon* dxCommon, Input* input, InputCamera* inputCamera, DebugText* text, PostEffect* post, SpriteManager* SpriteMan, Audio* audio)
{

	BaseScene::Initialize(dxCommon, input, inputCamera, text, post, SpriteMan, audio);

	SpriteMan->LoadTexture(0, L"Resources/SPACE.png");
	SpriteMan->LoadTexture(1, L"Resources/scenechenge.png");
	SpriteMan->LoadTexture(2, L"Resources/TITLE.png");
	SpriteMan->LoadTexture(3, L"Resources/black.png");
	
	spriteSceneChenge = new Sprite;
	spriteSPACE = new Sprite;
	TITLE = new Sprite;
	Black = new Sprite;
	
	spriteSPACE->Create(0);
	spriteSceneChenge->Create(1);
	TITLE->Create(2);
	Black->Create(3);

    Object3d::SetCamera(inputCamera);
    // ライト生成
	light = Light::Create();
	// 3Dオブエクトにライトをセット
	Object3d::SetLightGroup(light);
	light->SetSpotLightActive(0, true);
	light->SetSpotLightActive(1, true);
	light->SetCircleShadowActive(0, true);
	light->SetCircleShadowActive(1, true);
    //Object3d::SetLightGroup(light);
    mDome = Model::CreateOBJ("skydome");
    Dome = Object3d::Create(mDome);
	Dome->SetPosition({ 180,0,0 });
	Dome->SetRotation({ 0,0,0 });
	Dome->SetScale({ 3,3,3 });
    modelPlayerBody = Model::CreateOBJ("playerbody");
    modelPlayer = Model::CreateOBJ("playerobj");
	modelTitleObjs = Model::CreateOBJ("TitleObjs");
	mKey = Model::CreateOBJ("key");
    mBattery = Model::CreateOBJ("battery");
	mTitleMove = Model::CreateOBJ("titleobj");

	
	Key = Key::Create(mKey);
	// パーティクルマネージャ生成
	particleMan = ParticleManager::Create(dxCommon->GetDevice(), inputCamera);
	for (int i = 0; i < 9; i++)
	{
		TitleObjs[i] = Object3d::Create(modelTitleObjs);
		TitleObjs[i]->SetScale({ 1.2,1.2,1.2 });
		TitleObjs[i]->SetRotation({ 0,180,0 });
		TitleObjs[i]->SetPosition({ -12 + i * 3.f,55,-2 });
	}
	TitleMove[0] = Object3d::Create(mTitleMove);
	TitleMove[0]->SetPosition({ 0,40,0 });
	TitleMove[0]->SetScale({ 1.5,1.5,1.5 });
	TitleMove[0]->SetRotation({ 0,0,0 });

	TitleMove[1] = Object3d::Create(mTitleMove);
	TitleMove[1]->SetRotation({ 0,180,0 });
	TitleMove[1]->SetPosition({ 0,40,0 });
	TitleMove[1]->SetScale({ 1.5,1.5,1.5 });
	
	Key->SetScale({ 5,5,5 });
	Battery = Battery::Create(mBattery);
	Battery->SetScale({ 1.5,1.5,1.5 });
	Battery->SetPosition(BatteryPosition);
    objPlayerBody = Player::Create(modelPlayerBody);
    objPlayer = Player::Create(modelPlayer);
	
    objPlayerBody->SetScale({ 1.5,1.5,1.5 });
    objPlayer->SetScale({ 1.5,1.5,1.5 });
    
    stage = new Stage();
    stage->Initialize();
	Key->SetPosition(KeyPosition);
    inputCamera->SetTarget(CameraPosition);
    inputCamera->SetDistance(3.0f);
    inputCamera->SetEye(XMFLOAT3(Eye));
	objPlayerBody->SetPosition(PBodyPosition);
	objPlayer->SetPosition(PBodyPosition);
	post->SetStartFlag(false);
	post->SetPostFlag(false);
	post->ResetTime();
	objPlayerBody->SetMoveFlags(true);
	objPlayer->SetMoveFlags(true);
}



void TitleScene::Finalize()
{
   safe_delete(spriteSceneChenge);
   safe_delete(spriteSPACE);
   safe_delete(Black);
   safe_delete(TITLE);
   safe_delete(Dome);
   safe_delete(mDome);
   safe_delete(particleMan);
   
   
   safe_delete(light);
   safe_delete(stage);
   for (int i = 0; i < 9; i++)
   {
	   safe_delete(TitleObjs[i]);
   }
   safe_delete(objPlayerBody);
   
   safe_delete(objPlayer);
   safe_delete(Key);
   safe_delete(Battery);

   safe_delete(modelPlayerBody);
   safe_delete(modelPlayer);
   
   safe_delete(mKey);
   safe_delete(mBattery);
   safe_delete(mTitleMove);
   safe_delete(TitleMove[0]);
   safe_delete(TitleMove[1]);
   

}

void TitleScene::Update()
{

	
	if (input->Trigger(DIK_SPACE))
	{
		objPlayerBody->SetStartFlag(true);
		objPlayer->SetStartFlag(true);
		StartFlag = true;
	}

	if (StartFlag == false)
	{
		PBodyPosition = { 0,55,-2 };
		CameraPosition.x = PBodyPosition.x;
		CameraPosition.y = PBodyPosition.y - 5;
		CameraPosition.z = PBodyPosition.z - 15;
	}
	if(StartFlag)
	{
		TitleMove[0]->SetPosition({ 0,PBodyPosition.y,6 });
		TitleMove[1]->SetPosition({ 0,PBodyPosition.y,6 });
		if(PBodyPosition.y<45)
		CameraPosition.x = PBodyPosition.x;
		CameraPosition.y = PBodyPosition.y + 5;
		CameraPosition.z = PBodyPosition.z - 15;
		//影
		light->SetCircleShadowDir(0, XMVECTOR({ circleShadowDir[0] + PlayerShadowDir[0], circleShadowDir[1], circleShadowDir[2] + PlayerShadowDir[2], 0 }));
		light->SetCircleShadowCasterPos(0, XMFLOAT3({ PBodyPosition.x - PlayerShadow[0],PBodyPosition.y,PBodyPosition.z - PlayerShadow[2] }));
		light->SetCircleShadowAtten(0, XMFLOAT3(circleShadowAtten));
		light->SetCircleShadowFactorAngle(0, XMFLOAT2(circleShadowFactorAngle));

		//光
		light->SetSpotLightDir(0, XMVECTOR({ spotLightDir[0] - PlayerLight[0], spotLightDir[1], spotLightDir[2] - PlayerLight[2], 0 }));
		light->SetSpotLightPos(0, XMFLOAT3(PBodyPosition.x, PBodyPosition.y + spotLightPos[1], PBodyPosition.z));
		light->SetSpotLightColor(0, XMFLOAT3(spotLightColor));
		light->SetSpotLightAtten(0, XMFLOAT3(spotLightAtten));
		light->SetSpotLightFactorAngle(0, XMFLOAT2(spotLightFactorAngle));

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
				PlayerShadow[0] = -0.5;
				PlayerLight[0] = -0.5;
				PlayerShadowDir[0] = -0.5;
			}
			if (input->Push(DIK_A))
			{//ラグの問題でxに-1する
				//Bodyの回転
				objPlayer->SetRotation({ 0,270,0 });
				PlayerBodyRotz += 5;
				PlayerBodyRotx = 0;
				PlayerShadow[0] = 0.5;
				PlayerLight[0] = 0.5;
				PlayerShadowDir[0] = 0.5;
			}
			if (input->Push(DIK_A) && input->Push(DIK_D))
			{
				PlayerShadow[0] = 0;
				PlayerShadow[2] = 0;
				PlayerLight[0] = 0;
				PlayerLight[2] = 0;
				PlayerShadowDir[0] = 0;
				PlayerShadowDir[2] = 0;
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

				PlayerShadow[2] = -0.5;
				PlayerLight[2] = -0.5;
				PlayerShadowDir[2] = -0.5;

			}
			if (input->Push(DIK_S))
			{//ラグの問題でzに-1する
				//BodyとHeadの回転
				objPlayer->SetRotation({ 0,180,0 });
				PlayerBodyRotz = 90;
				PlayerBodyRotx -= 5;

				PlayerShadow[2] = +0.5;
				PlayerLight[2] = +0.5;
				PlayerShadowDir[2] = +0.5;
			}
			if (input->Push(DIK_S) && input->Push(DIK_W))
			{
				PlayerShadow[0] = 0;
				PlayerShadow[2] = 0;
				PlayerLight[0] = 0;
				PlayerLight[2] = 0;
				PlayerShadowDir[0] = 0;
				PlayerShadowDir[2] = 0;
			}
		}


	}
	else if (objPlayerBody->MoveCount == 0)
	{
		PlayerShadow[0] = 0;
		PlayerShadow[2] = 0;
		PlayerLight[0] = 0;
		PlayerLight[2] = 0;
		PlayerShadowDir[0] = 0;
		PlayerShadowDir[2] = 0;
	}
	
	
	PlayerPos[0] = PBodyPosition.x;
	PlayerPos[1] = PBodyPosition.y;
	PlayerPos[2] = PBodyPosition.z;

	CameraPos[0] = CameraPosition.x;
	CameraPos[1] = CameraPosition.y;
	CameraPos[2] = CameraPosition.z;

	KeyPos[0] = KeyPosition.x;
	KeyPos[1] = KeyPosition.y;
	KeyPos[2] = KeyPosition.z;
	
	BatPos[0] = BatteryPosition.x;
	BatPos[1] = BatteryPosition.y;
	BatPos[2] = BatteryPosition.z;
	
	inputCamera->SetTarget(CameraPosition);
	inputCamera->SetEye(XMFLOAT3(Eye));
	inputCamera->Update();

	objPlayerBody->SetRotation({ PlayerBodyRotx,PlayerBodyRoty,PlayerBodyRotz });
	objPlayerBody->SetPosition({ PBodyPosition });
	Key->SetPosition(KeyPosition);
	Battery->SetPosition(BatteryPosition);
	Dome->Update();
	light->Update();
	
	objPlayerBody->Update();
	objPlayer->Update();
	Key->Update(particleMan);
	Battery->Update();
	stage->GetCameraPos(CameraPosition);
	for (int i = 0; i < 9; i++)
	{
		TitleObjs[i]->Update();
	}
	if (Battery->BatFlag == false && PBodyPosition.z > -3 && PBodyPosition.y < 2)
	{
		TitleMove[0]->SetRotation({ 0,0,45 });
		TitleMove[1]->SetRotation({ 0,180,45 });
		if (a[0] < 0.5)
		{
			a[0] += 0.05;
		}	
		post->SetStartFlag(true);
	}
	
	if (Battery->BatFlag)
	{
		if (a[0] > 0.05)
		{
			a[0] -= 0.05;
		}
	}
	if (Key->KeyFlag)
	{
		stage->SetKeyFlag(Key->KeyFlag);
	}

	if (Key->KeyFlag && PlayerPos[0] > 3 && PlayerPos[2] > 68)
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
			SceneManager::GetInstance()->ChangeScene("GAME");
		}
	}
	spriteSceneChenge->SetPosition({ 640 - SpriteX[0], 360 - SpriteY[0] });
	spriteSceneChenge->SetSize({ SpriteX[0] * 2.0f, SpriteY[0] * 2.0f });
	
	
	
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
		spriteSPACE->SetAlpha(alpha[0]);
	
		TitleMove[0]->Update();
		TitleMove[1]->Update();

	Key->GetPos(PBodyPosition);
	Battery->GetPos(PBodyPosition);
	
	particleMan->Update();
	Black->SetAlpha(a[0]);
	stage->Stage0();
}

void TitleScene::Draw()
{
    
    // コマンドリストの取得
    ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	Object3d::PreDraw(cmdList);
    objPlayerBody->Draw();
    objPlayer->Draw();
	Key->Draw();
	if (StartFlag == false)
	{
		for (int i = 0; i < 9; i++)
		{
			TitleObjs[i]->Draw();
		}
	}
	else
	{
		TitleMove[0]->Draw();
		TitleMove[1]->Draw();
	}
	
	Battery->Draw();
    stage->StageObjDraw0();
    Dome->Draw();
	particleMan->Draw(cmdList);
	Object3d::PostDraw();
}

void TitleScene::Draw2D()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	//
	Sprite::PreDraw(cmdList);
	
	spriteSceneChenge->Draw();
	//spritepos->Draw();
	Sprite::PostDraw();
}
void TitleScene::FirstDraw2D()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	//
	Sprite::PreDraw(cmdList);
	if (StartFlag == false)
	{
		spriteSPACE->Draw();
		TITLE->Draw();
	}
	Black->Draw();
	Sprite::PostDraw();
}
void TitleScene::DrawImGui()
{
	ImGui::Begin("pos");
	ImGui::SetWindowPos(ImVec2(0, 0));
	ImGui::SetWindowSize(ImVec2(500, 200));
	ImGui::InputFloat3("PlayerPosition", PlayerPos);
	ImGui::InputFloat3("CameraPosition", CameraPos);
	ImGui::InputFloat3("Battery", BatPos);
	ImGui::InputFloat3("KeyPosition", KeyPos);
	ImGui::InputFloat2("al",a );
	ImGui::InputFloat("al",alpha );
	

	ImGui::End();
}

