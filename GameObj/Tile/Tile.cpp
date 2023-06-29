#include "Tile.h"
#include "Input.h"
Tile* Tile::Create(Model* model)
{
	// 3Dオブジェクトのインスタンスを生成
	Tile* instance = new Tile();
	if (instance == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!instance->Initialize()) {
		delete instance;
		assert(0);
	}

	if (model) {
		instance->SetModel(model);
	}

	return instance;
}

bool Tile::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}

	return true;
}

void Tile::Update(int Number)
{
	if (Number == 0 || Number % 2 == 0)
	{
		rotation = { 0, 0, 0 };
	}
	else
	{
		rotation = { 0, 180, 0 };
	}
 

    if (abs(position.x - pos.x) <= 10.0f && abs(position.y - pos.y) <= 5.0f && abs(position.z - pos.z) <= 10.0f)
    {
        if (Number == 0 || Number % 2 == 0)
        {
			if (Z)
			{
				MoveY += 0.3;
				if (MoveY < 1.5)
				{
					position.z -= 0.3;
				}
				else
				{
					Z = false;
				}
				
			}
			
			
        }
        else
        {
			if (Z2)
			{
				MoveY2 += 0.3;
				if (MoveY2 < 1.5)
				{
					position.z += 0.3;
				}
				else
				{
					Z2 = false;
				}
			}
        }
        
	}
	else
	{
		if (Number == 0 || Number % 2 == 0)
		{
			if (Z== false)
			{
				MoveY -= 0.3;
				if (MoveY > 0)
				{
					position.z += 0.3;
				}
				else
				{
					Z = true;
				}

			}


		}
		else
		{
			if (Z2== false)
			{
				MoveY2 -= 0.3;
				if (MoveY2 > 0)
				{
					position.z -= 0.3;
				}
				else
				{
					Z2 = true;
				}
			}
		}
	}
	
	Object3d::Update();
}

void Tile::Draw()
{
	Object3d::Draw();
}
