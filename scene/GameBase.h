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
	//�Q�[��
	virtual void Run();

	//������
	virtual void Initialize();

	//�I��
	virtual void Finalize();

	//���t���[��
	virtual void Update();

	//�`��
	virtual void Draw();

protected:
	// �ėp�@�\
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

