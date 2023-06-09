#include "GameMnager.h"
#include "SceneFactory.h"
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
	audio->SoundLoadWave("test.wav");
}

void GameMnager::Finalize()
{
	GameBase::Finalize();	
}

void GameMnager::Update()
{
	GameBase::Update();
	SceneManager::GetInstance()->Update(dxCommon, input, inputCamera, text, post, SpriteMan, audio);
	
	/*if (input->Push(DIK_0))
	{
		Times += 0.1f;
		post->SetStartFlag(true);
	}
	if (input->Push(DIK_1))
	{
		
		post->ResetTime();
	}
	
	
	*/
	if (post->GetStartFlag()==false)
	{

		post->ResetTime();
	}

	if (post->GetStartFlag())
	{
		Times = 0.1f;
	}
	
	post->Update(Times);
	audio->SoundPlayWave("test.wav",true);
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
	if (post->GetPostFlag()||post->GetStartFlag())
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
