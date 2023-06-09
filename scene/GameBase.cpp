#include "GameBase.h"

void GameBase::Run()
{
	Initialize();
	// ���C�����[�v
	while (true)
	{
		//Escape�L�[�Ń��[�v�𔲂���
		if (input->Push(DIK_ESCAPE))
		{
			return;
		}

		Update();
		Draw();

	}
	Finalize();
}

void GameBase::Initialize()
{

	// �Q�[���E�B���h�E�̍쐬
	win = new WinApp();
	win->CreateGameWindow();
	// ���͂̏�����
	input = Input::GetInstance();
	input->Initialize(win->GetInstance(), win->GetHwnd());

	//DirectX������
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(win);

	inputCamera = new InputCamera(win->window_width, win->window_height, input);
	SpriteMan = new SpriteManager();
	SpriteMan->Initialize(dxCommon);

	Sprite::StaticInitialize(dxCommon, SpriteMan);
	Object3d::StaticInitialize(dxCommon);
	text = DebugText::GetInstance();
	text->Initialize(textNumber);
	Light::StaticInitialize(dxCommon->GetDevice());

	audio = new Audio();
	audio->Initialize();

	post = new PostEffect();
	post->Initialize(dxCommon->GetDevice());
}

void GameBase::Finalize()
{
	// �e����

	safe_delete(input);
	safe_delete(dxCommon);
	safe_delete(light);


	delete(sceneFactory);
	// �Q�[���E�B���h�E�̔j��
	win->TerminateGameWindow();
	safe_delete(win);
}

void GameBase::Update()
{
	// ���b�Z�[�W����
	if (win->ProcessMessage()) { return; }


	// ���͊֘A�̖��t���[������
	input->Update();

}

void GameBase::Draw()
{

}