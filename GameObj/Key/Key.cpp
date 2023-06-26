#include "Key.h"

Key* Key::Create(Model* model)
{
	// 3Dオブジェクトのインスタンスを生成
	Key* instance = new Key();
	if (instance == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!instance->Initialize()) {
		delete instance;
		assert(0);
	}

	if (model) {
		instance->SetModel(model);
	}

	return instance;
}

bool Key::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}
	
	stage = new Stage();
	
    return true;
}

void Key::Update(ParticleManager* particleMan, Light* light)
{
	Object3d::Update();
	
	if (abs(position.x - pos.x) <= 0.8f && abs(position.y - pos.y) <= 5.0f && abs(position.z - pos.z) <= 0.8f)
	{
		KeyFlag = true;
		light->SetPointLightActive(0, false);
		light->SetCircleShadowActive(1, false);
	}
	if (KeyFlag)
	{
		if (time < 10)
		{
			time += 1;
			CreateParticle(particleMan);
		}
	}
	stage->SetKeyFlag(KeyFlag);

	if (Input::GetInstance()->Push(DIK_L))
	{
		light->SetPointLightActive(0, false);
	}
	else
	{
		light->SetPointLightActive(0, true);
	}
	light->SetPointLightPos(0, XMFLOAT3(position.x, position.y, position.z - 1));
	light->SetPointLightColor(0, XMFLOAT3(spotLightColor));
	
	light->SetCircleShadowCasterPos(1, XMFLOAT3(position.x, position.y-3, position.z));
	light->SetCircleShadowDir(1, XMVECTOR({ circleShadowDir[0],circleShadowDir[1],circleShadowDir[2], 0}));
	light->SetCircleShadowAtten(1, XMFLOAT3(circleShadowAtten));
	light->SetCircleShadowFactorAngle(1, XMFLOAT2(circleShadowFactorAngle));
}

void Key::CreateParticle(ParticleManager* particleMan)
{
	const float rnd_posx = 1.0f;
	const float rnd_posy = 1.0f;
	const float rnd_posz = 1.0f;

	const float rnd_vel = 0.4f;
	const float rnd_acc = 0.1f;

	for (int i = 0; i < 10; i++) {
		// 初期座標をランダムに生成
		XMFLOAT3 pos{};
		float angle = (float)rand() / RAND_MAX * 2.0f;  // ランダムな角度を生成
		float radius = (float)rand() / RAND_MAX * rnd_posx;     // ランダムな半径を生成

		pos.x = radius * cos(angle) + position.x;
		pos.y = radius * sin(angle) + position.y-2;
		pos.z = radius * sin(angle) + position.z;

		// 初速度をランダムに生成
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

		// 初加速度をランダムに生成
		XMFLOAT3 acc{};
	//	acc.y = -(float)rand() / RAND_MAX * rnd_acc;

		// パーティクルを追加
		particleMan->Add(20, pos, vel, acc, 0.4f, 0.0f);
	}
}

void Key::Draw()
{
	if (KeyFlag == false)
	{
		Object3d::Draw();
	}
}



void Key::GetPos(XMFLOAT3 pos)
{
	this->pos = pos;
}
