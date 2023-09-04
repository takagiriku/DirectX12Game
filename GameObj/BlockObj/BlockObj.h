#pragma once
#include"Object3d.h"

class Player;

class BlockObj :
	public Object3d
{
public:
	// 3D�I�u�W�F�N�g����
	static BlockObj* Create(Model* model = nullptr);

	void SetTilePos(std::vector<DirectX::XMFLOAT3> TilePos) { this->TilePos = TilePos; }
	void SetPlayer(Player* player) { this->player = player; }
	// ������
	bool Initialize()override;

	// ���t���[������
	void Update();

	void Draw();
	
	std::vector<DirectX::XMFLOAT3> TilePos;

	
private:

	bool SetPosFlag = false;
	Player* player = nullptr;
	XMFLOAT3 PlayerPos = { 0,0,0 };
	float BackmoveDistance = 1.0;
};

