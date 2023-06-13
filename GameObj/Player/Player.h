#pragma once
#include"ParticleManager.h"
#include "Object3d.h"
#include"Input.h"

class Game;

class Player:
	public Object3d
{
public:
	// 3D�I�u�W�F�N�g����
	static Player* Create(Model* model = nullptr);
public:

	// ������
	bool Initialize() override;

	// ���t���[������
	void Update() override;



	//DirectX::XMFLOAT3 GetPosition() const { return position; }

	ParticleManager* particleMan = nullptr;

	int GetMoveCount() const { return MoveCount; }

	
	void Foll();

	void Move();

	int scene = 0;

	
	bool StartFlag = false;

	void SetStartFlag(bool StartFlag) { this->StartFlag = StartFlag; }
	bool GetStartFlag() const { return StartFlag; }
	
	void SetMoveFlags(bool Flag) { this->MoveFlags = Flag; }
	bool GetMoveFlag() const {
		return this->MoveFlags;
	}
	
	bool MoveFlags = false;

	int MoveCount = 0;

private:

	bool onGround = true;

	// �����x�N�g��
	float fallV[4] = { 0,0,0,0 };

	int gameCount = 0;

	int MoveFlag = 0;
	
	//�ړ��ϐ�
	float moveDistance = 0.5;
	//�߂�
	float BackmoveDistance = 0.5;


	ParticleManager* particleManager = nullptr;
};



