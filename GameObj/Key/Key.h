#pragma once
#include"Object3d.h"
#include"GameObj/Stage/Stage.h"
#include"ParticleManager.h"
#include"light.h"

class ParticleManager;
class Light;
//キークラス
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
	//パーティクル
	void CreateParticle(ParticleManager* particleMan);
	//描画
	void Draw();
	//床の座標
	void SetTilePos(std::vector<DirectX::XMFLOAT3> TilePos) { this->TilePos = TilePos; }
	
	//プレイヤーの座標
	void SetPos(XMFLOAT3 pos);
	XMFLOAT3 pos = { 0,0,0 };

	void SetKeyFlag(bool StartFlag) { this->KeyFlag = StartFlag; }
	bool GetKeyFlag() const { return KeyFlag; }
	
	
	std::vector<DirectX::XMFLOAT3> TilePos;
	bool KeyFlag = false;
protected:
	bool SetPosFlag = false;
	//光
	float spotLightColor[3] = { 0.7f,0.8f,1 };
	//影
	float circleShadowDir[3] = { 0,-1,0 };
	float circleShadowAtten[3] = { 0.5f,0.6f,0.0f };
	float circleShadowFactorAngle[2] = { 0.0f, 0.5f };
	
	float time = 0;
};

