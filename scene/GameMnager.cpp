#include "GameMnager.h"
#include "SceneFactory.h"
#include <iostream>
GameMnager* GameMnager::GetInstance()
{
	static GameMnager instance;

	return &instance;
}

void GameMnager::Initialize()
{
	GameBase::Initialize();

	sceneFactory = new SceneFactory();
	SceneManager::GetInstance()->SetSceneFactory(sceneFactory);
	SceneManager::GetInstance()->ChangeScene("TITLE");
	
}

void GameMnager::Finalize()
{
	GameBase::Finalize();	
}

void GameMnager::Update()
{
	GameBase::Update();
	SceneManager::GetInstance()->Update(dxCommon, input, inputCamera, text, post, SpriteMan, audio);
	
	
	
	if (post->GetStartFlag()==false)
	{

		post->ResetTime();
	}

	if (post->GetStartFlag())
	{
		Times = 0.1f;
	}
	
	post->Update(Times);
	
	
}

void GameMnager::Draw()
{
	GameBase::Draw();
	// �`��J�n
	post->PreDrawScene(dxCommon->GetCommandList());
	SceneManager::GetInstance()->Draw();
	SceneManager::GetInstance()->Draw2D();
	post->PostDrawScene(dxCommon->GetCommandList());
	
	dxCommon->PreDraw();
	SceneManager::GetInstance()->DrawImGui();
	if (post->GetStartFlag())
	{
		post->Draw(dxCommon->GetCommandList());
		SceneManager::GetInstance()->FirstDraw2D();
	}
	else
	{
		SceneManager::GetInstance()->Draw();
		SceneManager::GetInstance()->Draw2D();
		SceneManager::GetInstance()->FirstDraw2D();
	}
	// �`��I��
	dxCommon->PostDraw();
}
