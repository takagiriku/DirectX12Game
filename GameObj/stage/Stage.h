#include"Object3d.h"
#include"SafeDelete.h"
#include"TouchableObject.h"
#include"SphereCollider.h"
#include <map>
#include"input.h"
#pragma once
class Player;
class TouchableObject;
struct LevelData;


class Stage
{

private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	Stage();

	~Stage();

	//������
	void Initialize();

	//�X�e�[�W��������
	void Generation();
	//�X�V
	void Update();
	//�`���[�g���A��
	void Stage0();
	
	void Stage1();
	
	void Stage3();
	
	void Stage4();
	
	void StageChange();

	bool ObjDraw0(const std::string& objectName) const;
	
	void StageObjDraw0();

	bool ObjDraw(const std::string& objectName) const;

	void StageObjDraw();

	

	void SetGenerationFlag(bool StartFlag) { GenerationFlag = StartFlag; }
	bool GetGenerationFlag() const { return GenerationFlag; }
	
	void SetKeyFlag(bool StartFlag) { KeyFlag = StartFlag; }
	bool GetKeyFlag() const { return KeyFlag; }
	

	int stagecount = 0;

	void GetCameraPos(XMFLOAT3 camerapos){ this->camerapos = camerapos; };
	XMFLOAT3 camerapos = { 0,0,0 };


	
	bool KeyFlag = false;

	float BoxCount = 0;

	XMFLOAT3 Gole = { 0,0,0 };
	std::vector<DirectX::XMFLOAT3> TilePosition;
	
	std::vector<DirectX::XMFLOAT3> TilePosition3;
private:
	LevelData* levelData = nullptr;
	
	Input* input = nullptr;
	Player* player = nullptr;
	
	Model* model = nullptr;
	Model* modelGround = nullptr;
	Model* modelSpaceWall = nullptr;
	Model* modelSpaceWall2 = nullptr;

	
	std::map<std::string, Model*> models;
	std::map<std::string, LevelData*> fileData;
	std::vector<Object3d*> objects;

	//�I�u�W�F�g�̖��O
	std::vector<std::string> ObjNames;
	std::vector<std::string> GetNames;
	const std::string skipFileTile = "tile";
	const std::string skipFileTile2 = "tile2";
	const std::string skipFileTile3 = "tile3";
	const std::string skipFileSlope = "slope";
	const std::string skipFileWall0 = "SpaceWall0";
	const std::string skipFileWall1 = "SpaceWall1";
	const std::string skipFileWall2 = "SpaceWall2";
	const std::string skipFileWall3 = "SpaceWall3";
	const std::string skipFileWall4 = "SpaceWall4";
	const std::string skipFileWall5 = "SpaceWall5";
	const std::string skipFileWall6 = "SpaceWall6";
	const std::string skipFileWall7 = "SpaceWall7";
	const std::string skipFileWall8 = "SpaceWall8";
	const std::string skipFileWall9 = "SpaceWall9";
	const std::string skipFileWall1Rot90 = "SpaceWall1Rot90";
	const std::string skipFileWall2Rot90 = "SpaceWall2Rot90";
	const std::string skipFileWall3Rot90 = "SpaceWall3Rot90";
	const std::string skipFileWall4Rot90 = "SpaceWall4Rot90";
	const std::string skipFileWall5Rot90 = "SpaceWall5Rot90";
	const std::string skipFileMoveWallRot90 = "moveWallRot90";
	const std::string skipFileWallsousa = "SpaceWallsousa";

	bool DrawFlag = false;

	bool GenerationFlag = false;

	XMFLOAT3 StagePos = { 0,0,0 };

	bool objMoveflag = false;
	float MaxPos = 0;
	float alpha = 1;
};