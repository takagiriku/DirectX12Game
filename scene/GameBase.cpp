#include "GameBase.h"

void GameBase::Run()
{
	Initialize();
	// メインループ
	while (true)
	{
		//Escapeキーでループを抜ける
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

	// ゲームウィンドウの作成
	win = new WinApp();
	win->CreateGameWindow();
	// 入力の初期化
	input = Input::GetInstance();
	input->Initialize(win->GetInstance(), win->GetHwnd());

	//DirectX初期化
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
	// 各種解放

	safe_delete(input);
	safe_delete(dxCommon);
	safe_delete(light);


	delete(sceneFactory);
	// ゲームウィンドウの破棄
	win->TerminateGameWindow();
	safe_delete(win);
}

void GameBase::Update()
{
	// メッセージ処理
	if (win->ProcessMessage()) { return; }


	// 入力関連の毎フレーム処理
	input->Update();

}

void GameBase::Draw()
{

}