#include "BlockObj.h"
#include"Player/Player.h"
#include <random>
#include "Input.h"
BlockObj* BlockObj::Create(Model* model)
{
	// 3Dオブジェクトのインスタンスを生成
	BlockObj* instance = new BlockObj();
	if (instance == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!instance->Initialize()) {
		delete instance;
		assert(0);
	}

	if (model) {
		instance->SetModel(model);
	}

	return instance;
}

bool BlockObj::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}
	return true;
	
}

void BlockObj::Update()
{
	Input* input = Input::GetInstance();
	if (!SetPosFlag)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrib(0, TilePos.size() - 1);
		int rand = distrib(gen);
		position = TilePos[rand];
		position.y = 3;
		SetPosFlag = true;
	}

	PlayerPos = player->GetPosition();
	XMFLOAT3 Ppos = PlayerPos;
	if (input->Push(DIK_D) || input->Push(DIK_A))
	{
		if (abs(position.x - PlayerPos.x) <= 2)
		{
			if (position.x < PlayerPos.x && abs(position.y - PlayerPos.y) <= 3 && abs(position.z - PlayerPos.z) <= 3)
			{
				player->MoveFlag[1] = 2;
			}
			if (position.x > PlayerPos.x && abs(position.y - PlayerPos.y) <= 3 && abs(position.z - PlayerPos.z) <= 3)
			{
				player->MoveFlag[1] = 1;
			}
		}

	}
	else if (input->Push(DIK_W) || input->Push(DIK_S))
	{
		if (abs(position.z - PlayerPos.z) <= 2)
		{
			if (position.z < PlayerPos.z && abs(position.y - PlayerPos.y) <= 3 && abs(position.x - PlayerPos.x) <= 3)
			{
				player->MoveFlag[1] = 3;
			}
			if (position.z > PlayerPos.z && abs(position.y - PlayerPos.y) <= 3 && abs(position.x - PlayerPos.x) <= 3)
			{
				player->MoveFlag[1] = 4;
			}
		}
	}
	
	
	switch (player->MoveFlag[1])
	{
	case 0:
		break;
	case 1:
		Ppos.x - BackmoveDistance;
		player->MoveFlag[1] = 5;
		break;
	case 2:
		Ppos.x + BackmoveDistance;
		player->MoveFlag[1] = 6;
		break;
	case 3:
		Ppos.z + BackmoveDistance;
		player->MoveFlag[1] = 7;
		break;
	case 4:
		Ppos.z - BackmoveDistance;
		player->MoveFlag[1] = 8;
		break;

	}
	player->SetPosition(Ppos);
	Object3d::Update();
}

void BlockObj::Draw()
{
	Object3d::Draw();
}
