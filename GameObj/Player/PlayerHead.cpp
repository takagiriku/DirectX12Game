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

	player = new Player;

	return true;
}



void PlayerHead::Update()
{

	
	SetPos(player->GetPosition());

	// 行列の更新など
	Object3d::Update();
}
