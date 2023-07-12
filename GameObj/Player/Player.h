#pragma once
#include "Object3d.h"
#include"Input.h"

class Light;
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

	
	void Foll();

	void Move();

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

private:
	float lightDir0[3] = { 0,0,1 };
	float lightColor0[3] = { 0,1,0 };
	//方向
	float lightDir1[3] = { 1,1,0 };
	float lightColor1[3] = { 0,1,0 };
	float lightDir2[3] = { 1,0,0 };
	float lightColor2[3] = { 0,0,1 };
	float spotLightDir[3] = { 0,-5,0 };
	float spotLightPos[3] = { 0,5,0 };
	float spotLightColor[3] = { 0.7f,0.8f,1 };
	float spotLightAtten[3] = { 0.0f,0.0f,0.0f };
	float spotLightFactorAngle[2] = { 20.0f, 30.0f };

	float circleShadowDir[3] = { 0,-1,0 };
	float circleShadowPos[3] = { 1,7,0 };
	float circleShadowAtten[3] = { 0.5f,0.6f,0.0f };
	float circleShadowFactorAngle[2] = { 0.0f, 0.5f };

	bool onGround = true;

	// 落下ベクトル
	float fallV[4] = { 0,0,0,0 };
	int MoveFlag = 0;
	

};



