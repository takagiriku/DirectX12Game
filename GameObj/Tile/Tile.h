#pragma once
#include "Object3d.h"
class Tile :
    public Object3d
{
public:
	// 3D�I�u�W�F�N�g����
	static Tile* Create(Model* model = nullptr);
public:

	// ������
	bool Initialize() override;

	// ���t���[������
	void Update(int Number);
	bool MoveFlag1 = false;
	bool MoveFlag2 = false;
	void Draw()override;
	void SetPos(XMFLOAT3 pos) { this->pos = pos; };
	XMFLOAT3 pos = { 0,0,0 };
	
	float MoveY = 0;
	float MoveY2 = 0;
	bool Z = true;
	bool Z2 = true;

	
};

