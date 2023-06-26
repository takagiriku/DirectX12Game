#include "Box.h"
#include "Input.h"
Box* Box::Create(Model* model)
{
	// 3Dオブジェクトのインスタンスを生成
	Box* instance = new Box();
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

	float distanceThresholdX = 1.5f;  // X軸方向の距離閾値
	float distanceThresholdY = 2.f;  // Y軸方向の距離閾値
	float distanceThresholdZ = 2.f;  // Z軸方向の距離閾値
	int minX = 1;  // X座標の最小値
	int maxX = 124;  // X座標の最大値
	int minZ = 1;  // Z座標の最小値
	int maxZ = 73;  // Z座標の最大値
	if (BoxFlag == false)
	{
		if (position.x >= minX && position.x <= maxX && position.z >= minZ && position.z <= maxZ)
		{
			if (abs(position.x - pos.x) <= distanceThresholdX && abs(position.y - pos.y) <= distanceThresholdY && abs(position.z - pos.z) <= distanceThresholdZ)
			{
				// PlayerがBoxに近づいた方向を判定する
				float directionX = pos.x - position.x;
				float directionZ = pos.z - position.z;

				// 逆方向に移動する
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
