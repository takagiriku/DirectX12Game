#pragma once
#include"Object3d.h"
#include"light.h"
class Battery :
	public Object3d
{
public:
	// 3D�I�u�W�F�N�g����
	static Battery* Create(Model* model = nullptr);
public:

	// ������
	bool Initialize() override;

	// ���t���[������
	void Update() override;

	void Draw()override;
	void GetPos(XMFLOAT3 pos);
	void SetBatFlag(bool StartFlag) { this->BatFlag = StartFlag; }
	XMFLOAT3 pos = { 0,0,0 };
	bool BatFlag = false;
	bool LifeFlag = false;
	
protected:
	Light* light = nullptr;
	

	
};
