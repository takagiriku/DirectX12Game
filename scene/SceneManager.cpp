#include "SceneManager.h"
#include <cassert>

SceneManager::~SceneManager()
{
	
	delete scene;
}

SceneManager* SceneManager::GetInstance()
{
	static SceneManager instance;
	return &instance;
}

void SceneManager::Update(DirectXCommon* dxCommon, Input* input, InputCamera* inputCamera, DebugText* text, PostEffect* post, SpriteManager* SpriteMan, Audio* audio)
{
	//ƒV[ƒ“‚ª‚ ‚é‚È‚ç
	if (nextScene)
	{
		if (scene)
		{
			
			delete scene;
		}
		scene = nextScene;
		nextScene = nullptr;

		scene->Initialize(dxCommon, input, inputCamera, text, post, SpriteMan, audio);
	}
	scene->Update();
}

void SceneManager::Draw()
{
	scene->Draw();

}

void SceneManager::Draw2D()
{
	scene->Draw2D();
}

void SceneManager::FirstDraw2D()
{
	scene->FirstDraw2D();
}

void SceneManager::DrawImGui()
{
	scene->DrawImGui();
}

void SceneManager::ChangeScene(const std::string& sceneName)
{
	assert(sceneFactory);
	assert(nextScene == nullptr);

	nextScene = sceneFactory->CreateScene(sceneName);
}
