#pragma once
#include"Object3d.h"

class Player;

class BlockObj :
	public Object3d
{
public:
	// 3Dオブジェクト生成
	static BlockObj* Create(Model* model = nullptr);

	void SetTilePos(std::vector<DirectX::XMFLOAT3> TilePos) { this->TilePos = TilePos; }
	void SetPlayer(Player* player) { this->player = player; }
	// 初期化
	bool Initialize()override;

	// 毎フレーム処理
	void Update();

	void Draw();
	
	std::vector<DirectX::XMFLOAT3> TilePos;

	
private:

	bool SetPosFlag = false;
	Player* player = nullptr;
	XMFLOAT3 PlayerPos = { 0,0,0 };
	float BackmoveDistance = 1.0;
};

