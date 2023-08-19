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
	void SetPlayer(Player* player);

	// 初期化
	bool Initialize() override;

	// 毎フレーム処理
	void Update();


	float ppos[3] = { 0,0,0 };

	
	int GetMoveCount() const { return MoveCount; }

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
	Player* player = nullptr;

	int gameCount = 0;

	int MoveFlag = 0;

};



