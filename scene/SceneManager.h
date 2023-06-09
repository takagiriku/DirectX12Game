#pragma once
#include"BaseScene.h"
#include "AbstractSceneFactory.h"
class SceneManager
{
public:
	static SceneManager* GetInstance();

	void Update(DirectXCommon* dxCommon, Input* input, InputCamera* inputCamera, DebugText* text, PostEffect* post, SpriteManager* SpriteMan, Audio* audio);

	void Draw();

	void Draw2D();

	void FirstDraw2D();

	void DrawImGui();

	void ChangeScene(const std::string& sceneName);

	void SetSceneFactory(AbstractSceneFactory* sceneFactory) { this->sceneFactory = sceneFactory; }
private:
	SceneManager() = default;
	~SceneManager();
	SceneManager(const SceneManager&) = delete;
	void operator=(const SceneManager&) = delete;
	AbstractSceneFactory* sceneFactory = nullptr;
	BaseScene* scene = nullptr;
	BaseScene* nextScene = nullptr;
};