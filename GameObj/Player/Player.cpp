#include "Player.h"
#include "Input.h"
#include "DebugText.h"
#include "SphereCollider.h"
#include "CollisionManager.h"
#include "CollisionAttribute.h"
#include"light.h"
using namespace DirectX;

Player* Player::Create(Model* model)
{
	// 3Dオブジェクトのインスタンスを生成
	Player* instance = new Player();
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

bool Player::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}

	position = { 1,3,0 };

	// コライダーの追加
	float radius = 0.6f;
	SetCollider(new SphereCollider(XMVECTOR({ 0,radius,0,0 }), radius));
	collider->SetAttribute(COLLISION_ATTR_ALLIES);

	return true;
}


void Player::Foll()
{
	// 落下処理
	if (!onGround) {
		// 下向き加速度
		const float fallAcc = -0.01f;
		const float fallVYMin = -0.8f;
		// 加速
		fallV[1] = (fallV[1] + fallAcc, fallVYMin);
		// 移動
		position.x += fallV[0];
		position.y += fallV[1];

	}
}

void Player::Move()
{

	SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(collider);
	assert(sphereCollider);
	
	//const float threshold = cosf(XMConvertToRadians(60.0f));

	// クエリーコールバッククラス
	class PlayerQueryCallback : public QueryCallback
	{
	public:
		PlayerQueryCallback(Sphere* sphere) : sphere(sphere) {};

		// 衝突時コールバック関数
		bool OnQueryHit(const QueryHit& info) {

			const XMVECTOR up = { 0,1,0,0 };

			XMVECTOR rejectDir = XMVector3Normalize(info.reject);
			float cos = XMVector3Dot(rejectDir, up).m128_f32[0];


			// 地面判定しきい値
			const float threshold = cosf(XMConvertToRadians(60.0f));

			if (-threshold < cos && cos < threshold) {
				sphere->center += info.reject;
				move += info.reject;
			}

			return true;
		}

		Sphere* sphere = nullptr;
		DirectX::XMVECTOR move = {};
	};
	PlayerQueryCallback callback(sphereCollider);

	// 球と地形の交差を全検索
	CollisionManager::GetInstance()->QuerySphere(*sphereCollider, &callback, COLLISION_ATTR_GROUND);
	// 交差による排斥分動かす
	position.x += callback.move.m128_f32[0];
	position.y += callback.move.m128_f32[1];
	//position.z += callback.move.m128_f32[2];
	// ワールド行列更新
	UpdateWorldMatrix();
	collider->Update();
	GroundCollision(sphereCollider);
	
}

void Player::GroundCollision(SphereCollider* sphereCollider)
{
	Input* input = Input::GetInstance();
	// 球の上端から球の下端までのレイキャスト
	Ray ray;
	ray.start = sphereCollider->center;
	ray.start.m128_f32[1] += sphereCollider->GetRadius();
	ray.dir = { 0,-1,0,0 };
	RaycastHit raycastHit;
	// 接地状態
	if (onGround) {
		// スムーズに坂を下る為の吸着距離
		const float adsDistance = 0.2f;

		//移動変数
		float moveDistance = 0.5;
		//戻り
		float BackmoveDistance = 0.5;
		// 接地を維持
		if (CollisionManager::GetInstance()->Raycast(ray, COLLISION_ATTR_GROUND, &raycastHit, sphereCollider->GetRadius() * 3.0f + adsDistance)) {
			onGround = true;
			position.y -= (raycastHit.distance - sphereCollider->GetRadius() * 3.0f);
			PlayerMove(input);

		}

		// 地面がないので落下
		else
		{
			//戻り
			switch (MoveFlag[0])
			{
			case 1:
				position.x -= BackmoveDistance;
				MoveFlag[0] = 5;
				MoveCount = 0;
				onGround = true;
				break;
			case 2:
				position.x += BackmoveDistance;
				MoveFlag[0] = 6;
				MoveCount = 0;
				onGround = true;
				break;
			case 3:
				position.z += BackmoveDistance;
				MoveFlag[0] = 7;
				MoveCount = 0;
				onGround = true;
				break;
			case 4:
				position.z -= BackmoveDistance;
				MoveFlag[0] = 8;
				MoveCount = 0;
				onGround = true;
				break;

			}
			onGround = false;
			fallV[1] = -1.0f;
		}

	}
	// 落下状態
	else if (fallV[1] <= 0.0f) {
		if (CollisionManager::GetInstance()->Raycast(ray, COLLISION_ATTR_GROUND, &raycastHit, sphereCollider->GetRadius() * 3.0f)) {
			// 着地
			onGround = true;
			position.y -= (raycastHit.distance - sphereCollider->GetRadius() * 3.0f);
		}
	}
}

void Player::MoveInputZ(float moveDistance, int moveFlag1, int moveFlag2, int moveCount)
{//Zの移動
	position.z += moveDistance;
	MoveFlag[0] = moveFlag1;
	MoveFlag[1] = moveFlag2;
	MoveCount = moveCount;
}

void Player::MoveInputX(float moveDistance, int moveFlag1, int moveFlag2, int moveCount)
{//Xの移動
	position.x += moveDistance;
	MoveFlag[0] = moveFlag1;
	MoveFlag[1] = moveFlag2;
	MoveCount = moveCount;
}

void Player::PlayerMove(Input* input)
{
	Sphere* sphere = dynamic_cast<Sphere*>(collider);

	
	if (MoveFlags)
	{
		//移動
		const float moveDistance = 0.5f;
		const float backMoveDistance = 0.5f;
		if (input->Push(DIK_D) || input->Push(DIK_A))
		{
			if (input->Push(DIK_D) && MoveFlag[0] != 5 && MoveFlag[1] != 5)
			{
				MoveInputX(moveDistance, 1, 0, 1);
				rotation.x += moveDistance * 10;
				rotation.y = 90;
			}
			if (input->Push(DIK_A) && MoveFlag[0] != 6 && MoveFlag[1] != 6)
			{
				MoveInputX(-moveDistance, 2, 0, 1);
				rotation.x -= moveDistance * 10;
				rotation.y = 90;
			}
		}
		else if (input->Push(DIK_W) || input->Push(DIK_S))
		{
			if (input->Push(DIK_S) && MoveFlag[0] != 7 && MoveFlag[1] != 7)
			{
				MoveInputZ(-moveDistance, 3, 0, 1);
				rotation.x -= moveDistance * 10;
				rotation.y = 0;
			}
			if (input->Push(DIK_W) && MoveFlag[0] != 8 && MoveFlag[1] != 8)
			{
				MoveInputZ(moveDistance, 4, 0, 1);
				rotation.x += moveDistance * 10;
				rotation.y = 0;
			}
		}		
	}
	
	
}


void Player::Update(Light* light)
{
	//影
	light->SetCircleShadowDir(0, XMVECTOR({ circleShadowDir[0] , circleShadowDir[1], circleShadowDir[2], 0 }));
	light->SetCircleShadowCasterPos(0, XMFLOAT3({ position }));
	light->SetCircleShadowAtten(0, XMFLOAT3(circleShadowAtten));
	light->SetCircleShadowFactorAngle(0, XMFLOAT2(circleShadowFactorAngle));

	//光
	light->SetSpotLightPos(0, XMFLOAT3(position.x, position.y+ spotLightPos[1], position.z));
	light->SetSpotLightDir(0, XMVECTOR({ spotLightDir[0], spotLightDir[1], spotLightDir[2] , 0 }));
	light->SetSpotLightColor(0, XMFLOAT3(spotLightColor));
	light->SetSpotLightAtten(0, XMFLOAT3(spotLightAtten));
	light->SetSpotLightFactorAngle(0, XMFLOAT2(spotLightFactorAngle));
	if (StartFlag)
	{
		Foll();
	}
	collider->Update();
	Move();

	pos = position;
	
	// 行列の更新など
	Object3d::Update();
}
