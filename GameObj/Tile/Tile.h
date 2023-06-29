#pragma once
#include "Object3d.h"
class Tile :
    public Object3d
{
public:
	// 3Dオブジェクト生成
	static Tile* Create(Model* model = nullptr);
public:

	// 初期化
	bool Initialize() override;

	// 毎フレーム処理
	void Update(int Number);
	bool MoveFlag1 = false;
	bool MoveFlag2 = false;
	void Draw()override;
	void SetPos(XMFLOAT3 pos) { this->pos = pos; };
	XMFLOAT3 pos = { 0,0,0 };
	
	float MoveY = 0;
	float MoveY2 = 0;
	bool Z = true;
	bool Z2 = true;

	
};

