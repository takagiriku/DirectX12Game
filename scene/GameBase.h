#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"
#include"SceneManager.h"
#include "AbstractSceneFactory.h"
#include"Sprite.h"
#include"Object3d.h"
#include "SafeDelete.h"
#include <DirectXMath.h>
#include "Input.h"
#include "ParticleManager.h"
#include "DebugText.h"
#include "InputCamera.h"
#include "Light.h"
#include "PostEffect.h"
#include"SceneManager.h"
#include"Audio.h"
#include"Data.h"
class GameBase
{
public:
	//ゲーム
	virtual void Run();

	//初期化
	virtual void Initialize();

	//終了
	virtual void Finalize();

	//毎フレーム
	virtual void Update();

	//描画
	virtual void Draw();

protected:
	// 汎用機能
	WinApp* win = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Input* input;
	PostEffect* post = nullptr;
	DebugText* text;
	InputCamera* inputCamera = nullptr;
	Light* light = nullptr;
	SpriteManager* SpriteMan = nullptr;
	AbstractSceneFactory* sceneFactory = nullptr;
	Audio* audio = nullptr;
	Data* data = nullptr;
	const int textNumber = 2;
};

