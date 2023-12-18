#include "Battery.h"
#include "Input.h"
Battery* Battery::Create(Model* model)
{
	// 3D�I�u�W�F�N�g�̃C���X�^���X�𐶐�
	Battery* instance = new Battery();
	if (instance == nullptr) {
		return nullptr;
	}

	// ������
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

	
	return true;
}

void Battery::Update(ParticleManager* particleMan, PostEffect* post, Light* light, int Number)
{
	float Speed = 1;
	float ResetTime = 400;

	if (!BatFlag)
	{
		if (abs(position.x - pos.x) <= 1.f && abs(position.y - pos.y) <= 5.0f && abs(position.z - pos.z) <= 1.f)
		{//����������
			BatFlag = true;
			post->ClearTime();
			light->SetPointLightActive(Number, false);
			light->SetCircleShadowActive(Number + 1, false);
		}
	}
	else
	{
		Time += Speed;
		if (Time < ResetTime/40)
		{//�������p�[�e�B�N��
			CreateParticle(particleMan);
		}
	}
	if (Time > ResetTime)
	{//����
		Time = 0;
		BatFlag = false;
		light->SetPointLightActive(Number, true);
		light->SetCircleShadowActive(Number + 1, true);
	}


	rotation.y += Speed;
	rotation.x = 30;
	
	Object3d::Update();

	
	light->SetPointLightPos(Number, XMFLOAT3(position.x, position.y, position.z - 1));
	light->SetPointLightColor(Number, XMFLOAT3(spotLightColor));
	light->SetCircleShadowCasterPos(Number + 1, XMFLOAT3(position.x, position.y-1, position.z));
	light->SetCircleShadowDir(Number + 1, XMVECTOR({ circleShadowDir[0],circleShadowDir[1],circleShadowDir[2], 0 }));
	light->SetCircleShadowAtten(Number + 1, XMFLOAT3(circleShadowAtten));
	light->SetCircleShadowFactorAngle(Number + 1, XMFLOAT2(circleShadowFactorAngle));
	
}
void Battery::CreateParticle(ParticleManager* particleMan)
{
	const float rnd_posx = 1.0f;
	const float rnd_posy = 2.0f;
	const float rnd_posz = 1.0f;

	const float rnd_vel = 0.4f;
	const float rnd_acc = 0.1f;

	for (int i = 0; i < 5; i++) {
		// �������W�������_���ɐ���
		XMFLOAT3 pos{};
		float angle = (float)rand() / RAND_MAX * 2.0f;  // �����_���Ȋp�x�𐶐�
		float radius = (float)rand() / RAND_MAX * rnd_posx;     // �����_���Ȕ��a�𐶐�

		pos.x = radius * cos(angle) + position.x;
		pos.y = radius * sin(angle) + position.y;
		pos.z = radius * sin(angle) + position.z;

		// �����x�������_���ɐ���
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

		// �������x�������_���ɐ���
		XMFLOAT3 acc{};
		//	acc.y = -(float)rand() / RAND_MAX * rnd_acc;

			// �p�[�e�B�N����ǉ�
		particleMan->Add(20, pos, vel, acc, 0.4f, 0.0f);
	}
}


void Battery::Draw()
{
	if (!BatFlag)
	{
		Object3d::Draw();
	}
}

void Battery::SetPos(XMFLOAT3 pos)
{
	this->pos = pos;
}
