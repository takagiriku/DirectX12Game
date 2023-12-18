#pragma once
#include"Object3d.h"
#include"light.h"
#include"ParticleManager.h"
#include"PostEffect.h"
class PostEffect;
class ParticleManager;
class Light;
class Battery :
	public Object3d
{
private:
public:
	// 3D�I�u�W�F�N�g����
	static Battery* Create(Model* model = nullptr);
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:

	// ������
	bool Initialize() override;

	// ���t���[������
	void Update(ParticleManager* particleMan, PostEffect* post, Light* light,int Number);
	//�p�[�e�B�N��
	void CreateParticle(ParticleManager* particleMan);
	//�`��
	void Draw()override;
	//�v���C���[�̍��W
	void SetPos(XMFLOAT3 pos);
	XMFLOAT3 pos = { 0,0,0 };

	void SetBatFlag(bool StartFlag) { this->BatFlag = StartFlag; }
	bool GetBatFlag() const {
		return this->BatFlag;
	}
	bool BatFlag = false;

	
protected:
	//��
	float spotLightColor[3] = { 0.7f,0.8f,1 };
	//�e
	float circleShadowDir[3] = { 0,-1,0 };
	float circleShadowAtten[3] = { 0.5f,0.6f,0.0f };
	float circleShadowFactorAngle[2] = { 0.0f, 0.5f };

	float Time = 0;
	
};
