#include"GameScene.h"
#include"GameBase.h"
#include"TitleScene.h"
#include<vector>


//ゲームマネジャー
class GameMnager : public GameBase
{
public:
	GameMnager* GetInstance();
public:
	//初期化
	void Initialize() override;

	//終了
	virtual void Finalize() override;

	//毎フレーム
	virtual void Update() override;

	//描画
	virtual void Draw() override;
	void SetPostFlag(bool StartFlag) { this->PostFlag = StartFlag; }
	bool PostFlag = false;
protected:
	float time = 0;
	float Times = 0.f;

	
};
