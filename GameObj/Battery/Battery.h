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
	//パーティクル
	void CreateParticle(ParticleManager* particleMan);
	//描画
	void Draw()override;
	//プレイヤーの座標
	void SetPos(XMFLOAT3 pos);
	XMFLOAT3 pos = { 0,0,0 };

	void SetBatFlag(bool StartFlag) { this->BatFlag = StartFlag; }
	bool GetBatFlag() const {
		return this->BatFlag;
	}
	bool BatFlag = false;

	
protected:
	//光
	float spotLightColor[3] = { 0.7f,0.8f,1 };
	//影
	float circleShadowDir[3] = { 0,-1,0 };
	float circleShadowAtten[3] = { 0.5f,0.6f,0.0f };
	float circleShadowFactorAngle[2] = { 0.0f, 0.5f };

	float Time = 0;
	
};
