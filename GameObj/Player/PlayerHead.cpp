#include "PlayerHead.h"
#include "Player.h"
#include "Input.h"

PlayerHead* PlayerHead::Create(Model* model)
{
	// 3Dオブジェクトのインスタンスを生成
	PlayerHead* instance = new PlayerHead();
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

bool PlayerHead::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}

	

	return true;
}

void PlayerHead::Update()
{
	Input* input = Input::GetInstance();
	
	if (player) {
		position = player->GetPosition();
	}

	if (input->Push(DIK_A) || input->Push(DIK_D))
	{
		if (input->Push(DIK_D))
		{	
			rotation.y = 90;
		}
		if (input->Push(DIK_A))
		{
			rotation.y = 270;
		}

	}
	else if (input->Push(DIK_S) || input->Push(DIK_W))
	{
		if (input->Push(DIK_W))
		{
			rotation.y = 0;
		}
		if (input->Push(DIK_S))
		{
			rotation.y = 180;
		}

	}
	ppos[0] = position.x;
	ppos[1] = position.y;
	ppos[2] = position.z;
	Object3d::Update();
}
