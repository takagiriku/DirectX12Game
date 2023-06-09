#pragma once
#include "Object3d.h"
class Box :
    public Object3d
{
public:
	// 3Dオブジェクト生成
	static Box* Create(Model* model = nullptr);
public:

	// 初期化
	bool Initialize() override;

	// 毎フレーム処理
	void Update() override;

	void Draw()override;
	void GetPos(XMFLOAT3 pos);
	void SetBoxFlag(bool StartFlag) { this->BoxFlag = StartFlag; }
	bool GetBoxFlag() const { return this->BoxFlag; }
	XMFLOAT3 pos = { 0,0,0 };
	bool BoxFlag = false;
	bool MoveFlag = false;
	float FlagCount = 0;


};

