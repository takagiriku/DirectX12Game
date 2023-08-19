#include "TitleScene.h"
#include"SceneManager.h"
#include <base/SafeDelete.h>
#include"GameObj/Player/Player.h"
#include"GameObj/Player/PlayerHead.h"
#include"GameObj/stage/stage.h"
#include"GameObj/key/Key.h"
#include"GameObj/Battery/Battery.h"
#include"GameObj/BackObj/BackObj.h"

void TitleScene::Initialize(DirectXCommon* dxCommon, Input* input, InputCamera* inputCamera, DebugText* text, PostEffect* post, SpriteManager* SpriteMan, Audio* audio)
{

	BaseScene::Initialize(dxCommon, input, inputCamera, text, post, SpriteMan, audio);

	data = new Data();
	data->SetStageCount(0);
	data->Initialize();

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
	light->SetPointLightActive(0, true);
	light->SetPointLightActive(2, true);
	
	light->SetCircleShadowActive(0, true);
	light->SetCircleShadowActive(1, true);
	light->SetCircleShadowActive(2, true);
	//Object3d::SetLightGroup(light);
   
	data->Dome->SetPosition({ 180,0,0 });
	data->Dome->SetRotation({ 0,0,0 });
	data->Dome->SetScale({ 3,3,3 });
    mBack = Model::CreateOBJ("backobj");

	
	// パーティクルマネージャ生成
	particleMan = ParticleManager::Create(dxCommon->GetDevice(), inputCamera);
	for (int i = 0; i < 9; i++)
	{
		data->TitleObjs[i]->SetScale({ 1.2,1.2,1.2 });
		data->TitleObjs[i]->SetRotation({ 0,180,0 });
		data->TitleObjs[i]->SetPosition({ -12 + i * 3.f,55,-2 });
	}
	data->TitleMove[0]->SetRotation({ 0,0,0 });
	data->TitleMove[0]->SetPosition({ 0,40,0 });
	data->TitleMove[0]->SetScale({ 1.5,1.5,1.5 });

	data->TitleMove[1]->SetRotation({ 0,180,0 });
	data->TitleMove[1]->SetPosition({ 0,40,0 });
	data->TitleMove[1]->SetScale({ 1.5,1.5,1.5 });
	
	data->Keys[0]->SetScale({5,5,5});
	data->battery[0]->SetScale({1.5,1.5,1.5});
	data->battery[0]->SetPosition(BatteryPosition);
 
	data->objPlayer->SetPlayer(data->objPlayerBody);
	
	data->objPlayerBody->SetScale({ 1.5,1.5,1.5 });
	data->objPlayer->SetScale({ 1.5,1.5,1.5 });
    
	
    stage = new Stage();
    stage->Initialize();
	data->Keys[0]->SetPosition(KeyPosition);
    inputCamera->SetTarget(CameraPosition);
    inputCamera->SetDistance(3.0f);
    inputCamera->SetEye(XMFLOAT3(Eye));
	data->objPlayerBody->SetPosition(PBodyPosition);
	data->objPlayer->SetPosition(PBodyPosition);

	post->SetStartFlag(false);
	
	post->ResetTime();
	data->objPlayerBody->SetMoveFlags(true);
	data->objPlayer->SetMoveFlags(true);
	
	audio->SoundStop("se_amc04.wav");
	audio->SoundLoadWave("digitalworld.wav");


}


void TitleScene::Finalize()
{
   safe_delete(spriteSceneChenge);
   safe_delete(spriteSPACE);
   safe_delete(Black);
   safe_delete(TITLE);
   safe_delete(particleMan);
   safe_delete(light);
   safe_delete(stage);
   safe_delete(mBack);
   
   data->Finalize();

}

void TitleScene::Update()
{
	audio->SoundPlayWave("digitalworld.wav", true);
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
	
	inputCamera->SetTarget(CameraPosition);
	inputCamera->SetEye(XMFLOAT3(Eye));
	inputCamera->Update();
	
	data->Keys[0]->SetPosition(KeyPosition);
	data->battery[0]->SetPosition(BatteryPosition);
	data->Dome->Update();
	
	
	data->objPlayerBody->Update(light);
	data->objPlayer->Update();
	data->Keys[0]->Update(particleMan, light);
	
	
	data->battery[0]->Update(particleMan, post, light, 2);
	stage->GetCameraPos(CameraPosition);
	
	light->Update();
	for (int i = 0; i < 9; i++)
	{
		data->TitleObjs[i]->Update();
	}
	if (data->battery[0]->BatFlag == false && PBodyPosition.z > -3 && PBodyPosition.y < 2)
	{
		data->TitleMove[0]->SetRotation({ 0,0,45 });
		data->TitleMove[1]->SetRotation({ 0,180,45 });
		if (a[0] < 0.3)
		{
			a[0] += 0.05;
		}	
		post->SetStartFlag(true);
	}
	
	if (data->battery[0]->BatFlag)
	{
		if (a[0] > 0.05)
		{
			a[0] -= 0.05;
		}
	}
	if (data->Keys[0]->KeyFlag)
	{
		stage->SetKeyFlag(data->Keys[0]->KeyFlag);
	}
	
	if (data->Keys[0]->KeyFlag && PBodyPosition.x > 3 && PBodyPosition.z > 68)
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
			SceneManager::GetInstance()->ChangeScene("GAME");
		}
	}
	spriteSceneChenge->SetPosition({ 640 - SpriteX[0], 360 - SpriteY[0] });
	spriteSceneChenge->SetSize({ SpriteX[0] * 2.0f, SpriteY[0] * 2.0f });
	
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
		spriteSPACE->SetAlpha(alpha[0]);
	
		data->TitleMove[0]->Update();
		data->TitleMove[1]->Update();

		data->Keys[0]->SetPos(PBodyPosition);
		data->battery[0]->SetPos(PBodyPosition);
	
	particleMan->Update();
	Black->SetAlpha(a[0]);
	stage->Stage0();
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
	Sprite::PreDraw(cmdList);
	if (StartFlag == false)
	{
		spriteSPACE->Draw();
		TITLE->Draw();
	}
	//Black->Draw();
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
