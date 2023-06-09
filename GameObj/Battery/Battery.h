#pragma once
#include"Object3d.h"
#include"light.h"
class Battery :
	public Object3d
{
public:
	// 3Dオブジェクト生成
	static Battery* Create(Model* model = nullptr);
public:

	// 初期化
	bool Initialize() override;

	// 毎フレーム処理
	void Update() override;

	void Draw()override;
	void GetPos(XMFLOAT3 pos);
	void SetBatFlag(bool StartFlag) { this->BatFlag = StartFlag; }
	XMFLOAT3 pos = { 0,0,0 };
	bool BatFlag = false;
	bool LifeFlag = false;
	
protected:
	Light* light = nullptr;
	

	
};
