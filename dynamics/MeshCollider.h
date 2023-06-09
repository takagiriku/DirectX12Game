﻿#pragma once

#include "BaseCollider.h"
#include "CollisionPrimitive.h"

#include <DirectXMath.h>

// メッシュ衝突判定オブジェクト
class MeshCollider :
	public BaseCollider
{
public:
	MeshCollider()
	{
		// メッシュ形状をセット
		shapeType = COLLISIONSHAPE_MESH;
	}

	// 三角形の配列を構築する
	void ConstructTriangles(Model* model);

	void Mechtriangles(Model* model);

	// 更新
	void Update() override;

	// 球との当たり判定
	bool CheckCollisionSphere(const Sphere& sphere, DirectX::XMVECTOR* inter = nullptr, DirectX::XMVECTOR* reject = nullptr);

	// レイとの当たり判定
	bool CheckCollisionRay(const Ray& ray, float* distance = nullptr, DirectX::XMVECTOR* inter = nullptr);

private:
	std::vector<Triangle> triangles;
	// ワールド行列の逆行列
	DirectX::XMMATRIX invMatWorld;
};

