#pragma once
#include "Object3d.h"
#include"Input.h"
class Player;
class Game;

class PlayerHead :
	public Object3d
{
	
public:
	// 3Dオブジェクト生成
	static PlayerHead* Create(Model* model = nullptr);
public:

	// 初期化
	bool Initialize() override;

	// 毎フレーム処理
	void Update() override;



	//DirectX::XMFLOAT3 GetPosition() const { return position; }

	
	int GetMoveCount() const { return MoveCount; }


	void SetPos(XMFLOAT3 position) { this->position = position; }
	
	

	//void Move();

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


	int gameCount = 0;

	int MoveFlag = 0;




	Player* player = nullptr;
};



