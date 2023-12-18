#pragma once
#include "Object3d.h"
#include"Input.h"

class Light;
class SphereCollider;
class Player:
	public Object3d
{
public:
	// 3Dオブジェクト生成
	static Player* Create(Model* model = nullptr);
public:

	// 初期化
	bool Initialize() override;

	// 毎フレーム処理
	void Update(Light* light);

	int GetMoveCount() const { return MoveCount; }
	//落下
	void Foll();
	//移動
	void Move();
	
	void MoveInputZ(float moveDistance, int moveFlag1, int moveFlag2, int moveCount);

	void MoveInputX(float moveDistance, int moveFlag1, int moveFlag2, int moveCount);

	void PlayerMove(Input* input);

	//地面
	void GroundCollision(SphereCollider* sphereCollider);
	
	
	const XMFLOAT3& GetPositions() { return pos; }
	int scene = 0;
	
	XMFLOAT3 pos{};
	
	bool StartFlag = false;

	void SetStartFlag(bool StartFlag) { this->StartFlag = StartFlag; }
	bool GetStartFlag() const { return StartFlag; }
	
	void SetMoveFlags(bool Flag) { this->MoveFlags = Flag; }
	bool GetMoveFlag() const {
		return this->MoveFlags;
	}
	
	bool MoveFlags = false;

	int MoveCount = 0;
	int MoveFlag[2] = {0,0};

	
private:
	//光
	float spotLightPos[3] = { 0,5,0 };
	float spotLightDir[3] = { 0,-5,0 };
	float spotLightColor[3] = { 0.7f,0.8f,1 };
	float spotLightAtten[3] = { 0.0f,0.0f,0.0f };
	float spotLightFactorAngle[2] = { 20.0f, 30.0f };
	//影
	float circleShadowDir[3] = { 0,-1,0 };
	float circleShadowAtten[3] = { 0.5f,0.6f,0.0f };
	float circleShadowFactorAngle[2] = { 0.0f, 0.5f };

	bool onGround = true;

	// 落下ベクトル
	float fallV[4] = { 0,0,0,0 };
	
};



