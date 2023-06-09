#include "Battery.h"

Battery* Battery::Create(Model* model)
{
	// 3Dオブジェクトのインスタンスを生成
	Battery* instance = new Battery();
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

bool Battery::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}

	//light = Light::Create();
	//Object3d::SetLightGroup(light);
	//light->SetPointLightActive(0, true);
	//light->SetCircleShadowActive(0, true);
	//Object3d::SetLightGroup(light);
	return true;
}

void Battery::Update()
{
	if (LifeFlag == false)
	{
		if (abs(position.x - pos.x) <= 1.0f && abs(position.y - pos.y) <= 5.0f && abs(position.z - pos.z) <= 1.0f)
		{
			BatFlag = true;
			LifeFlag = true;
		}
	}
	rotation.y += 1;
	rotation.x = 30;
	//light->SetSpotLightPos(0, XMFLOAT3(pos));
	//light->SetCircleShadowCasterPos(0, XMFLOAT3(pos));
	Object3d::Update();
	//light->Update();
}

void Battery::Draw()
{
	if (LifeFlag == false)
	{
		Object3d::Draw();
	}
}

void Battery::GetPos(XMFLOAT3 pos)
{
	this->pos = pos;
}
