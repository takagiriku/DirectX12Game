#pragma once
#include "Object3d.h"
class Box :
    public Object3d
{
public:
	// 3D�I�u�W�F�N�g����
	static Box* Create(Model* model = nullptr);
public:

	// ������
	bool Initialize() override;

	// ���t���[������
	void Update() override;

	void Draw()override;
	void GetPos(XMFLOAT3 pos);
	void SetBoxFlag(bool StartFlag) { this->BoxFlag = StartFlag; }
	bool GetBoxFlag() const { return this->BoxFlag; }
	XMFLOAT3 pos = { 0,0,0 };
	bool BoxFlag = false;
	bool MoveFlag = false;
	float FlagCount = 0;


};

