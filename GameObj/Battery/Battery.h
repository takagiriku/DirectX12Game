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
	// 3Dオブジェクト生成
	static Battery* Create(Model* model = nullptr);
public:

	// 初期化
	bool Initialize() override;

	// 毎フレーム処理
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
