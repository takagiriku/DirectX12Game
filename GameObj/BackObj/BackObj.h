#pragma once
#include "Object3d.h"

class Player;
class BackObj :
    public Object3d
{
public:
	// 3Dオブジェクト生成
	static BackObj* Create(Model* model = nullptr);

	void SetPlayer(Player* plyaer);
public:
	float count[1] = {0};
	// 初期化
	bool Initialize();

	// 毎フレーム処理
	void Update();

	void Draw();
private:
	Player* player = nullptr;
	XMFLOAT3 pos;
	XMFLOAT3 Ppos;
	bool flag = false;

	
};

