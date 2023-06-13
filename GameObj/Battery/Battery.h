#pragma once
#include"Object3d.h"
#include"light.h"
#include"ParticleManager.h"
#include"PostEffect.h"
class PostEffect;
class ParticleManager;
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
	void Update(ParticleManager* particleMan, PostEffect* post);

	void CreateParticle(ParticleManager* particleMan);

	void Draw()override;
	void GetPos(XMFLOAT3 pos);
	void SetBatFlag(bool StartFlag) { this->BatFlag = StartFlag; }
	bool GetBatFlag() const {
		return this->BatFlag;
	}
	XMFLOAT3 pos = { 0,0,0 };
	bool BatFlag = false;
	bool LifeFlag = false;
	
protected:
	Light* light = nullptr;
	
	float Time = 0;
	
};
