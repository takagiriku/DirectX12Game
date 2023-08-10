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
	// 3D�I�u�W�F�N�g�̃C���X�^���X�𐶐�
	Player* instance = new Player();
	if (instance == nullptr) {
		return nullptr;
	}

	// ������
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

	// �R���C�_�[�̒ǉ�
	float radius = 0.6f;
	SetCollider(new SphereCollider(XMVECTOR({ 0,radius,0,0 }), radius));
	collider->SetAttribute(COLLISION_ATTR_ALLIES);

	return true;
}


void Player::Foll()
{
	// ��������
	if (!onGround) {
		// �����������x
		const float fallAcc = -0.01f;
		const float fallVYMin = -0.8f;
		// ����
		fallV[1] = (fallV[1] + fallAcc, fallVYMin);
		// �ړ�
		position.x += fallV[0];
		position.y += fallV[1];

	}
	// �W�����v����
	else if (Input::GetInstance()->Push(DIK_SPACE)) {
		onGround = false;
		const float jumpVYFist = 0.1f;
		fallV[0] = { 0 };
		fallV[1] = { jumpVYFist };
		fallV[2] = { 0 };
		fallV[3] = { 0 };
	}
}

void Player::Move()
{
	Input* input = Input::GetInstance();

	SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(collider);
	assert(sphereCollider);
	
	//const float threshold = cosf(XMConvertToRadians(60.0f));

	// �N�G���[�R�[���o�b�N�N���X
	class PlayerQueryCallback : public QueryCallback
	{
	public:
		PlayerQueryCallback(Sphere* sphere) : sphere(sphere) {};

		// �Փˎ��R�[���o�b�N�֐�
		bool OnQueryHit(const QueryHit& info) {

			const XMVECTOR up = { 0,1,0,0 };

			XMVECTOR rejectDir = XMVector3Normalize(info.reject);
			float cos = XMVector3Dot(rejectDir, up).m128_f32[0];


			// �n�ʔ��肵�����l
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

	// ���ƒn�`�̌�����S����
	CollisionManager::GetInstance()->QuerySphere(*sphereCollider, &callback, COLLISION_ATTR_GROUND);
	// �����ɂ��r�˕�������
	position.x += callback.move.m128_f32[0];
	position.y += callback.move.m128_f32[1];
	//position.z += callback.move.m128_f32[2];
	// ���[���h�s��X�V
	UpdateWorldMatrix();
	collider->Update();

	// ���̏�[���狅�̉��[�܂ł̃��C�L���X�g
	Ray ray;
	ray.start = sphereCollider->center;
	ray.start.m128_f32[1] += sphereCollider->GetRadius();
	ray.dir = { 0,-1,0,0 };
	RaycastHit raycastHit;
	// �ڒn���
	if (onGround) {
		// �X���[�Y�ɍ������ׂ̋z������
		const float adsDistance = 0.2f;

		//�ړ��ϐ�
		float moveDistance = 0.5;
		//�߂�
		float BackmoveDistance = 0.5;
		// �ڒn���ێ�
		if (CollisionManager::GetInstance()->Raycast(ray, COLLISION_ATTR_GROUND, &raycastHit, sphereCollider->GetRadius() * 3.0f + adsDistance)) {
			onGround = true;
			position.y -= (raycastHit.distance - sphereCollider->GetRadius() * 3.0f);
			if (MoveFlags)
			{
				

				if (input->Push(DIK_D) || input->Push(DIK_A))
				{
					if (MoveFlag != 5)
					{
						if (input->Push(DIK_D))
						{
							position.x += moveDistance;
							MoveFlag = 1;
							MoveCount = 1;
							rotation.x += moveDistance * 10;
							rotation.y = 90;
						}
					}
					if (MoveFlag != 6)
					{
						if (input->Push(DIK_A))
						{
							position.x -= moveDistance;
							MoveFlag = 2;
							MoveCount = 1;
							rotation.x -= moveDistance * 10;
							rotation.y = 90;
						}
					}

				}
				else if (input->Push(DIK_W) || input->Push(DIK_S))
				{
					if (MoveFlag != 7)
					{
						if (input->Push(DIK_S))
						{
							position.z -= moveDistance;
							MoveFlag = 3;
							MoveCount = 1;
							rotation.x -= moveDistance * 10;
							rotation.y = 0;
						}
					}
					if (MoveFlag != 8)
					{
						if (input->Push(DIK_W))
						{
							position.z += moveDistance;
							MoveFlag = 4;
							MoveCount = 1;
							rotation.x += moveDistance * 10;
							rotation.y = 0;
						}
					}
				}
			}
			

		}

		// �n�ʂ��Ȃ��̂ŗ���
		else
		{
			switch (MoveFlag)
			{
			case 1:
				position.x -= BackmoveDistance;
				MoveFlag = 5;
				MoveCount = 0;
				onGround = true;
				break;
			case 2:
				position.x += BackmoveDistance;
				MoveFlag = 6;
				MoveCount = 0;
				onGround = true;
				break;
			case 3:
				position.z += BackmoveDistance;
				MoveFlag = 7;
				MoveCount = 0;
				onGround = true;
				break;
			case 4:
				position.z -= BackmoveDistance;
				MoveFlag = 8;
				MoveCount = 0;
				onGround = true;
				break;
			
			}			
			onGround = false;
			fallV[1] = -1.0f;
		}

	}
	// �������
	else if (fallV[1] <= 0.0f) {
		if (CollisionManager::GetInstance()->Raycast(ray, COLLISION_ATTR_GROUND, &raycastHit, sphereCollider->GetRadius() * 3.0f)) {
			// ���n
			onGround = true;
			position.y -= (raycastHit.distance - sphereCollider->GetRadius() * 3.0f);
		}
	}
}


void Player::Update(Light* light)
{
	//�e
	light->SetCircleShadowDir(0, XMVECTOR({ circleShadowDir[0] , circleShadowDir[1], circleShadowDir[2], 0 }));
	light->SetCircleShadowCasterPos(0, XMFLOAT3({ position }));
	light->SetCircleShadowAtten(0, XMFLOAT3(circleShadowAtten));
	light->SetCircleShadowFactorAngle(0, XMFLOAT2(circleShadowFactorAngle));

	//��
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
	
	// �s��̍X�V�Ȃ�
	Object3d::Update();
}
