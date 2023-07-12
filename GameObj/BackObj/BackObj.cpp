#include "BackObj.h"
#include"Player/Player.h"
#include"Input.h"
BackObj* BackObj::Create(Model* model)
{
	// 3Dオブジェクトのインスタンスを生成
	BackObj* instance = new BackObj();
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


bool BackObj::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}
	position = { 8,3,22 };
	return true;
}

void BackObj::Update()
{
	Input* input = Input::GetInstance();
	if (player) {
		Ppos = player->GetPosition();
		count[0] = Ppos.x - position.x + Ppos.z - position.z;
	}
	if (count[0] > 5)
	{
		flag = true;
	}
	else
	{
		flag = false;
	}
	Object3d::Update();
}

void BackObj::Draw()
{

	if (flag)
	{
		Object3d::Draw();
	}
	
}
void BackObj::SetPlayer(Player* player)
{
	this->player = player;
}