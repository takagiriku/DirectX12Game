#include "PlayerHead.h"
#include "Player.h"
#include "Input.h"


PlayerHead* PlayerHead::Create(Model* model)
{
	// 3D�I�u�W�F�N�g�̃C���X�^���X�𐶐�
	PlayerHead* instance = new PlayerHead();
	if (instance == nullptr) {
		return nullptr;
	}

	// ������
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

	// �s��̍X�V�Ȃ�
	Object3d::Update();
}
