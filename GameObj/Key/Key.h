#pragma once
#include"Object3d.h"
#include"GameObj/Stage/Stage.h"
#include"ParticleManager.h"
#include"light.h"

class ParticleManager;
class Light;
class Key:
	public Object3d
{
public:
	// 3Dオブジェクト生成
	static Key* Create(Model* model = nullptr);
public:

	// 初期化
	bool Initialize() ;

	// 毎フレーム処理
	void Update(ParticleManager* particleMan, Light* light) ;

	void CreateParticle(ParticleManager* particleMan);
	
	void Draw();
	void SetTilePos(std::vector<DirectX::XMFLOAT3> TilePos) { this->TilePos = TilePos; }
	void SetKeyFlag(bool StartFlag) { this->KeyFlag = StartFlag; }
	bool GetKeyFlag() const {
		return this->KeyFlag;
	}
	void SetPos(XMFLOAT3 pos);
	XMFLOAT3 pos = { 0,0,0 };
	std::vector<DirectX::XMFLOAT3> TilePos;
	bool KeyFlag = false;
protected:
	bool SetPosFlag = false;
	float spotLightColor[3] = { 0.7f,0.8f,1 };
	float circleShadowDir[3] = { 0,-1,0 };
	float circleShadowAtten[3] = { 0.5f,0.6f,0.0f };
	float circleShadowFactorAngle[2] = { 0.0f, 0.5f };
	
	float time = 0;
};

