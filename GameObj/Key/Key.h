#pragma once
#include"Object3d.h"
#include"GameObj/Stage/Stage.h"
#include"ParticleManager.h"

class ParticleManager;
class Key:
	public Object3d
{
public:
	// 3D�I�u�W�F�N�g����
	static Key* Create(Model* model = nullptr);
public:

	// ������
	bool Initialize() ;

	// ���t���[������
	void Update(ParticleManager* particleMan) ;

	void CreateParticle(ParticleManager* particleMan);
	
	void Draw();

	void SetKeyFlag(bool StartFlag) { this->KeyFlag = StartFlag; }
	bool GetKeyFlag() const {
		return this->KeyFlag;
	}
	void GetPos(XMFLOAT3 pos);
	XMFLOAT3 pos = { 0,0,0 };
	bool KeyFlag = false;
protected:
	float time = 0;
	Stage* stage = nullptr;
	
};

