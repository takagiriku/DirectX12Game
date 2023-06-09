#include "Key.h"

Key* Key::Create(Model* model)
{
	// 3D�I�u�W�F�N�g�̃C���X�^���X�𐶐�
	Key* instance = new Key();
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

bool Key::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}
	
	stage = new Stage();
	//stage->Initialize();
	
    return true;
}

void Key::Update(ParticleManager* particleMan)
{
	Object3d::Update();
	
	if (abs(position.x - pos.x) <= 1.0f && abs(position.y - pos.y) <= 5.0f && abs(position.z - pos.z) <= 1.0f)
	{
		KeyFlag = true;
	}
	if (KeyFlag)
	{
		time += 1;
		if (time < 25)
		{
			CreateParticle(particleMan);
		}
	}
	stage->SetKeyFlag(KeyFlag);
	
}

void Key::CreateParticle(ParticleManager* particleMan)
{
	const float rnd_posx = 1.0f;
	const float rnd_posy = 1.0f;
	const float rnd_posz = 1.0f;

	const float rnd_vel = 0.4f;
	const float rnd_acc = 0.1f;

	for (int i = 0; i < 10; i++) {
		// �������W�������_���ɐ���
		XMFLOAT3 pos{};
		float angle = (float)rand() / RAND_MAX * 2.0f;  // �����_���Ȋp�x�𐶐�
		float radius = (float)rand() / RAND_MAX * rnd_posx;     // �����_���Ȕ��a�𐶐�

		pos.x = radius * cos(angle) + position.x;
		pos.y = (float)rand() / RAND_MAX * rnd_posy - rnd_posy / 2.0f + position.y;
		pos.z = radius * sin(angle) + position.z;

		// �����x�������_���ɐ���
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel * 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

		// �������x�������_���ɐ���
		XMFLOAT3 acc{};
		acc.y = -(float)rand() / RAND_MAX * rnd_acc;

		// �p�[�e�B�N����ǉ�
		particleMan->Add(20, pos, vel, acc, 0.4f, 0.0f);
	}
}

void Key::Draw()
{
	if (KeyFlag == false)
	{
		Object3d::Draw();
	}
	//stage->StageObjDraw();
}



void Key::GetPos(XMFLOAT3 pos)
{
	this->pos = pos;
}
