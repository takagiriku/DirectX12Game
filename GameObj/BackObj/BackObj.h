#pragma once
#include "Object3d.h"

class Player;
class BackObj :
    public Object3d
{
public:
	// 3D�I�u�W�F�N�g����
	static BackObj* Create(Model* model = nullptr);

	void SetPlayer(Player* plyaer);
public:
	float count[1] = {0};
	// ������
	bool Initialize();

	// ���t���[������
	void Update();

	void Draw();
private:
	Player* player = nullptr;
	XMFLOAT3 pos;
	XMFLOAT3 Ppos;
	bool flag = false;

	
};

