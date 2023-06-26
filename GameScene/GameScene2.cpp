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
	// ���C�g����
	light = Light::Create();
	// 3D�I�u�G�N�g�Ƀ��C�g���Z�b�g
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
	if (objPlayerBody->MoveCount == 1)
		//�v���C���[�̏���
	{
		if (input->Push(DIK_A) || input->Push(DIK_D))
		{
			if (input->Push(DIK_D))
			{//���O�̖���x��+1����
				//Body��Head�̉�]
				objPlayer->SetRotation({ 0,90,0 });
				PlayerBodyRotz -= 5;
				PlayerBodyRotx = 0;

			}
			if (input->Push(DIK_A))
			{//���O�̖���x��-1����
				//Body�̉�]
				objPlayer->SetRotation({ 0,270,0 });
				PlayerBodyRotz += 5;
				PlayerBodyRotx = 0;
			}
		
		}
		else if (input->Push(DIK_S) || input->Push(DIK_W))
		{
			if (input->Push(DIK_W))
			{//���O�̖���z��+1����
				//Body��Head�̉�]
				objPlayer->SetRotation({ 0,0,0 });
				PlayerBodyRotx += 5;
				PlayerBodyRotz = 90;
			}
			if (input->Push(DIK_S))
			{//���O�̖���z��-1����
				//Body��Head�̉�]
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

	BatPos[0] = BoxPosition[0].x;
	BatPos[1] = BoxPosition[0].y;
	BatPos[2] = BoxPosition[0].z;


	objPlayerBody->SetRotation({ PlayerBodyRotx,PlayerBodyRoty,PlayerBodyRotz });
	Dome->Update();
	light->Update();

	for (int i = 0; i < 4; i++)
	{
		Battery[i]->Update(particleMan, post, light,i+2);
		Battery[i]->GetPos(PBodyPosition);
		Battery[i]->SetPosition(BatteryPosition[i]);
		Box[i]->Update();
		Box[i]->GetPos(PBodyPosition);
		//Box[i]->SetPosition(BoxPosition[i]);
		BBox[i]->Update();
	}

	Key->SetPosition(KeyPosition);
	Key->Update(particleMan, light);
	Key->GetPos(PBodyPosition);

	objPlayerBody->Update(light);
	objPlayer->Update(light);

	
	if (Key->KeyFlag)
	{
		Time += 1;
		if (Time < 200)
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
			FlagCount[i] = 1;
			
		}
		else
		{
			break;  // 1�ł��t���O�� false �̏ꍇ�̓��[�v���I������
		}
	}
	if (FlagCount[0] == 1 && FlagCount[1] == 1 && FlagCount[2] == 1 && FlagCount[3] == 1)
	{
		Key->SetKeyFlag(true);
	}
	float Gole = 56;
	if (Key->KeyFlag && abs(PBodyPosition.x - Gole) <= 10&& PBodyPosition.z > 73)
	{
		objPlayerBody->SetMoveFlags(false);
		objPlayer->SetMoveFlags(false);
		if (SpriteX[0] < 1280) // SpriteX����ʂ̒��S�܂ňړ�����܂�
		{
			SpriteX[0] += 12.8;
			SpriteY[0] += 7.4;
		}
		if (SpriteX[0] > 1270)
		{
			stage->StageChange();
			SceneManager::GetInstance()->ChangeScene("CLEAR");
		}
	}
	
	if (AlphaFlag)
	{
		if (alpha[0] < 1)
		{
			alpha[0] += 0.0005;
		}
	}
	if (AlphaFlag == false)
	{
		if (alpha[0] > 0.05)
		{
			alpha[0] -= 0.005;
		}
		else
		{
			AlphaFlag = true;
		}
	}
	if (alpha[0] > 1)
	{
		stage->StageChange();
		SceneManager::GetInstance()->ChangeScene("END");
	}

	Black->SetAlpha(alpha[0]);
	spriteSceneChenge->SetPosition({ 640 - SpriteX[0], 360 - SpriteY[0] });
	spriteSceneChenge->SetSize({ SpriteX[0] * 2.0f, SpriteY[0] * 2.0f });
	particleMan->Update();
	stage->Stage3();
	stage->GetCameraPos(CameraPosition);
	inputCamera->SetTarget(CameraPosition);
	inputCamera->SetEye(XMFLOAT3(Eye));
	inputCamera->Update();
}

void GameScene2::Draw()
{

	// �R�}���h���X�g�̎擾
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

	stage->StageObjDraw2();
	Dome->Draw();
	particleMan->Draw(cmdList);
	Object3d::PostDraw();


}

void GameScene2::Draw2D()
{

	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	Sprite::PreDraw(cmdList);
	spriteSceneChenge->Draw();
	Sprite::PostDraw();
}

void GameScene2::FirstDraw2D()
{

	// �R�}���h���X�g�̎擾
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
	ImGui::End();
}
