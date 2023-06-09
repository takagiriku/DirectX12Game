#pragma once
#include"input.h"
#include"DirectXCommon.h"
#include"Sprite.h"
#include"Object3d.h"
#include"inputCamera.h"
#include"DebugText.h"
#include"PostEffect.h"
#include"SpriteManager.h"
#include"Audio.h"
class SceneManager;

class BaseScene
{

public:
	BaseScene();
	virtual void Initialize(DirectXCommon* dxCommon, Input* input, InputCamera* inputCamera, DebugText* text, PostEffect* post, SpriteManager* SpriteMan, Audio* audio);

	virtual ~BaseScene() = default;


	virtual void Finalize() = 0;

	virtual void Update() = 0;

	virtual void Draw() = 0;

	virtual void Draw2D() = 0;

	virtual void FirstDraw2D() = 0;

	virtual void DrawImGui() = 0;

protected:
	BaseScene* nextScene = nullptr;

	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	InputCamera* inputCamera = nullptr;
	DebugText* text = nullptr;
	PostEffect* post = nullptr;
	SpriteManager* SpriteMan = nullptr;
	Audio* audio = nullptr;
	bool StartFlag = false;
};
