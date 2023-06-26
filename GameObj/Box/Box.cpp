#include "Box.h"
#include "Input.h"
Box* Box::Create(Model* model)
{
	// 3D�I�u�W�F�N�g�̃C���X�^���X�𐶐�
	Box* instance = new Box();
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

bool Box::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}

	return true;
}

void Box::Update()
{
	float posx[4] = { 1,124,1,124 };
	float posz[4] = { 1,1,73,73 };

	float distanceThresholdX = 1.5f;  // X�������̋���臒l
	float distanceThresholdY = 2.f;  // Y�������̋���臒l
	float distanceThresholdZ = 2.f;  // Z�������̋���臒l
	int minX = 1;  // X���W�̍ŏ��l
	int maxX = 124;  // X���W�̍ő�l
	int minZ = 1;  // Z���W�̍ŏ��l
	int maxZ = 73;  // Z���W�̍ő�l
	if (BoxFlag == false)
	{
		if (position.x >= minX && position.x <= maxX && position.z >= minZ && position.z <= maxZ)
		{
			if (abs(position.x - pos.x) <= distanceThresholdX && abs(position.y - pos.y) <= distanceThresholdY && abs(position.z - pos.z) <= distanceThresholdZ)
			{
				// Player��Box�ɋ߂Â��������𔻒肷��
				float directionX = pos.x - position.x;
				float directionZ = pos.z - position.z;

				// �t�����Ɉړ�����
				if (abs(directionX) >= abs(directionZ))
				{
					position.x -= directionX;
				}
				else
				{
					position.z -= directionZ;
				}

				position.x = (position.x < minX) ? minX : (position.x > maxX) ? maxX : position.x;
				position.z = (position.z < minZ) ? minZ : (position.z > maxZ) ? maxZ : position.z;
			}
		}
	}
	
	for (int i = 0; i < 4; i++)
	{
		if (abs(position.x - posx[i]) <= 1 && abs(position.z - posz[i]) <= 1)
		{
			BoxFlag = true;
			if (position.y > 9)
			{
				position.y -= 0.1;
			}
		}
	}
	Object3d::Update();
}

void Box::Draw()
{

	Object3d::Draw();
}

void Box::GetPos(XMFLOAT3 pos)
{
	this->pos = pos;
}
