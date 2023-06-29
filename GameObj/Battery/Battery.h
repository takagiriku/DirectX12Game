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
	// 3Dオブジェクト生成
	static Battery* Create(Model* model = nullptr);
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:

	// 初期化
	bool Initialize() override;

	// 毎フレーム処理
	void Update(ParticleManager* particleMan, PostEffect* post, Light* light,int Number);



	void CreateParticle(ParticleManager* particleMan);

	void Draw()override;
	void SetPos(XMFLOAT3 pos);
	void SetBatFlag(bool StartFlag) { this->BatFlag = StartFlag; }
	bool GetBatFlag() const {
		return this->BatFlag;
	}
	XMFLOAT3 pos = { 0,0,0 };
	bool BatFlag = false;

	
protected:
	float lightDir0[3] = { 0,0,1 };
	float lightColor0[3] = { 0,1,0 };
	//方向
	float lightDir1[3] = { 1,1,0 };
	float lightColor1[3] = { 0,1,0 };
	float lightDir2[3] = { 1,0,0 };
	float lightColor2[3] = { 0,0,1 };
	float spotLightDir[3] = { 0,-1,0 };
	float spotLightPos[3] = { 0,5,0 };
	float spotLightColor[3] = { 0.7f,0.8f,1 };
	float spotLightAtten[3] = { 0.0f,0.0f,0.0f };
	float spotLightFactorAngle[2] = { 20.0f, 30.0f };
	
	float circleShadowDir[3] = { 0,-1,0 };
	float circleShadowPos[3] = { 1,7,0 };
	float circleShadowAtten[3] = { 0.5f,0.6f,0.0f };
	float circleShadowFactorAngle[2] = { 0.0f, 0.5f };
	float Time = 0;
	
};
