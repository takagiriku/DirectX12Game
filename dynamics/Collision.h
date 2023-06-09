﻿#pragma once

#include "CollisionPrimitive.h"

// 当たり判定ヘルパークラス
class Collision
{
public:
	// 点と三角形の最近接点を求める
	static void ClosestPtPoint2Triangle(const DirectX::XMVECTOR& point, const Triangle& triangle, DirectX::XMVECTOR* closest);

	// 球と球の当たり判定
	static bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB, DirectX::XMVECTOR*inter = nullptr, DirectX::XMVECTOR * reject = nullptr);
	
	// 球と平面の当たり判定
	static bool CheckSphere2Plane(const Sphere& sphere, const Plane& plane, DirectX::XMVECTOR*inter = nullptr);

	// 球と法線付き三角形の当たり判定
	static bool CheckSphere2Triangle(const Sphere& sphere, const Triangle& triangle, DirectX::XMVECTOR* inter = nullptr, DirectX::XMVECTOR * reject = nullptr);

	// レイと平面の当たり判定
	static bool CheckRay2Plane(const Ray& lay, const Plane& plane, float*distance = nullptr, DirectX::XMVECTOR*inter = nullptr);

	// レイと法線付き三角形の当たり判定
	static bool CheckRay2Triangle(const Ray& lay, const Triangle& triangle, float*distance = nullptr, DirectX::XMVECTOR* inter = nullptr);

	// レイと球の当たり判定
	static bool CheckRay2Sphere(const Ray& lay, const Sphere& sphere, float*distance = nullptr, DirectX::XMVECTOR* inter = nullptr);
};