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
	SceneManager::GetInstance()->ChangeScene("GAME2");
	//audio->SoundLoadWave("digitalworld.wav");
}

void GameMnager::Finalize()
{
	GameBase::Finalize();	
}

void GameMnager::Update()
{
	GameBase::Update();
	SceneManager::GetInstance()->Update(dxCommon, input, inputCamera, text, post, SpriteMan, audio);
	
	if (input->Push(DIK_0))
	{
		Times += 0.1f;
		post->SetStartFlag(true);
	}
	if (input->Push(DIK_1))
	{
		
		post->ClearTime();
	}
	
	if (post->GetStartFlag()==false)
	{

		post->ResetTime();
	}

	if (post->GetStartFlag())
	{
		Times = 0.1f;
	}
	
	post->Update(Times);
	audio->SoundPlayWave("digitalworld.wav",true);
	
}

void GameMnager::Draw()
{
	GameBase::Draw();
	// •`‰æŠJŽn
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
	// •`‰æI—¹
	dxCommon->PostDraw();
}
