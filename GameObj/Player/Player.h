#pragma once
#include"ParticleManager.h"
#include "Object3d.h"
#include"Input.h"

class Game;

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
	void Update() override;



	//DirectX::XMFLOAT3 GetPosition() const { return position; }

	ParticleManager* particleMan = nullptr;

	int GetMoveCount() const { return MoveCount; }

	
	void Foll();

	void Move();

	int scene = 0;

	
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

	bool onGround = true;

	// 落下ベクトル
	float fallV[4] = { 0,0,0,0 };

	int gameCount = 0;

	int MoveFlag = 0;
	
	//移動変数
	float moveDistance = 0.5;
	//戻り
	float BackmoveDistance = 0.5;


	ParticleManager* particleManager = nullptr;
};



