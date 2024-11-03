#include"Stage.h"
#include"GameObj/Player/Player.h"
#include "LevelLoader.h"
#include <random>
Stage::Stage()
{
	GenerationFlag = false;
	stagecount = 0;
	MaxPos = 0;
}

Stage::~Stage()
{
	// ���f���̉��
	safe_delete(modelGround);
	safe_delete(modelSpaceWall);
	safe_delete(modelSpaceWall2);

	// ���������I�u�W�F�N�g�̉��
	for (auto& object : objects) {
		delete object;
	}
	objects.clear();
	GetNames.clear();
}

void Stage::Initialize()
{

	modelGround = Model::CreateOBJ("tile");
	modelSpaceWall = Model::CreateOBJ("spacewall");
	modelSpaceWall2 = Model::CreateOBJ("spacewall2");


	models.insert(std::make_pair("tile", modelGround));
	models.insert(std::make_pair("tile2", modelGround));
	models.insert(std::make_pair("tile3", modelGround));
	models.insert(std::make_pair("SpaceWall0", modelSpaceWall));
	models.insert(std::make_pair("SpaceWall1", modelSpaceWall));
	models.insert(std::make_pair("SpaceWall2", modelSpaceWall));
	models.insert(std::make_pair("SpaceWall3", modelSpaceWall));
	models.insert(std::make_pair("SpaceWall4", modelSpaceWall));
	models.insert(std::make_pair("SpaceWall5", modelSpaceWall));
	models.insert(std::make_pair("SpaceWall6", modelSpaceWall));
	models.insert(std::make_pair("SpaceWall7", modelSpaceWall));
	models.insert(std::make_pair("SpaceWall8", modelSpaceWall));
	models.insert(std::make_pair("SpaceWall9", modelSpaceWall));
	models.insert(std::make_pair("moveWallRot90", modelSpaceWall));
	models.insert(std::make_pair("SpaceWall1Rot90", modelSpaceWall));
	models.insert(std::make_pair("SpaceWall2Rot90", modelSpaceWall));
	models.insert(std::make_pair("SpaceWall3Rot90", modelSpaceWall));
	models.insert(std::make_pair("SpaceWall4Rot90", modelSpaceWall));
	models.insert(std::make_pair("SpaceWall5Rot90", modelSpaceWall));
	models.insert(std::make_pair("SpaceWallsousa", modelSpaceWall2));

}
void Stage::Generation()
{

	
	if (GenerationFlag == false)
	{
		if (!(stagecount == 3))
		{
			const std::vector<std::string> fileNames = { "Stage0",  "Stage1", "Stage2", "Stage3-1","Stage4" };
			const std::vector<LevelData*> fileDatas = LevelLoader::LoadFile(fileNames);
			for (size_t i = 0; i < fileNames.size(); i++) {
				fileData.insert(std::make_pair(fileNames[i], fileDatas[i]));
			}
			auto it = fileData.find(fileNames[stagecount]);
			if (it != fileData.end()) {
				levelData = it->second;
			}

		}
		
		if (stagecount == 3) {
			const std::vector<std::string> Stage3 = { "Stage3-1","Stage3-2","Stage3-3","Stage3-4","Stage3-5","Stage3-6" };
		
			const std::vector<LevelData*> fileDatas = LevelLoader::LoadFile(Stage3);
			
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> distrib(0, Stage3.size() - 1);
			int rand = distrib(gen);

			std::string selectedStage = Stage3[rand];
		
			for (size_t i = 0; i < Stage3.size(); i++) {
				fileData.insert(std::make_pair(Stage3[i], fileDatas[i]));
			}
			auto it = fileData.find(selectedStage);
			if (it != fileData.end()) {
				levelData = it->second;
			}
		}


		// ���x���f�[�^����I�u�W�F�N�g�𐶐��A�z�u
		for (auto& objectData : levelData->objects) {
			// �t�@�C��������o�^�ς݃��f��������
			Model* model = nullptr;
			decltype(models)::iterator it = models.find(objectData.fileName);
			if (it != models.end()) {
				model = it->second;
			}

			// ���f�����w�肵��3D�I�u�W�F�N�g�𐶐�
			Object3d* newObject;

			if (objectData.fileName == skipFileTile || objectData.fileName == skipFileTile2 || objectData.fileName == skipFileTile3) {
				newObject = TouchableObject::Create(model);
			}
			else {
				newObject = Object3d::Create(model);
			}

			// ���W
			DirectX::XMFLOAT3 pos;
			DirectX::XMStoreFloat3(&pos, objectData.translation);
			newObject->SetPosition(pos);

			// ��]�p
			DirectX::XMFLOAT3 rot;
			DirectX::XMStoreFloat3(&rot, objectData.rotation);
			newObject->SetRotation(rot);

			// �T�C�Y
			DirectX::XMFLOAT3 scale;
			DirectX::XMStoreFloat3(&scale, objectData.scaling);
			newObject->SetScale(scale);

			
			// �z��ɓo�^
			objects.push_back(newObject);
			GetNames.push_back(objectData.fileName);
		}
		GenerationFlag = true;
	}
}

void Stage::Update()
{

	if (GenerationFlag == false)
	{
		Generation();
	}

	if (KeyFlag || BoxCount > 0)
	{
		for (int i = 0; i < GetNames.size(); ++i)
		{
			if (GetNames[i] == skipFileMoveWallRot90)
			{
				DirectX::XMFLOAT3 Position = objects[i]->GetPosition();
				float speed = 0.05;
				float MoveY = Position.y + speed; // ���̑��x�œ���
				Gole = Position;

				if (MoveY < MaxPos)
				{
					objects[i]->SetPosition({ Position.x, MoveY, Position.z });
				}
				else if (BoxCount == 2)
				{
					MaxPos = 0; // MaxPos��0�ɐݒ�

					if (MoveY > MaxPos)
					{
						MoveY -= speed; // ���̑��x�ŉ��Ɉړ�
						objects[i]->SetPosition({ Position.x, MoveY, Position.z });
					}
				}

			}
		
			objects[i]->Update();
		}
	}
	else
	{
		for (int i = 0; i < GetNames.size(); ++i)
		{
			objects[i]->Update();
			if (GetNames[i] == skipFileTile)
			{
				TilePosition.push_back(objects[i]->GetPosition());
			}
			if (GetNames[i] == skipFileTile3)
			{
				TilePosition3.push_back(objects[i]->GetPosition());
			}
		}
	}
	
	StagePos = camerapos;
}
void Stage::Stage0()
{
	stagecount = 0;
	MaxPos = 13;
	Stage::Update();
	
}
void Stage::Stage1()
{
	stagecount = 1;
	MaxPos = 22;
	Stage::Update();

}

void Stage::Stage3()
{
	stagecount = 3;

	MaxPos = 14 + 2 * BoxCount;
	Stage::Update();
}
void Stage::Stage4()
{
	stagecount = 4;

	MaxPos = 22;
	Stage::Update();
}
void Stage::StageChange()
{
	// ���������I�u�W�F�N�g�̉��
	for (auto& object : objects) {
		delete object;
	}
	objects.clear();
	GetNames.clear();
}
void Stage::StageObjDraw0()
{
	for (int i = 0; i < GetNames.size(); ++i) {
		if (ObjDraw0(GetNames[i])) {
			objects[i]->Draw();
		}
	}
}

bool Stage::ObjDraw0(const std::string& objectName) const
{
	if (objectName == skipFileWall0) {
		return false;
	}

	bool shouldDraw = false;
	if (objectName == skipFileTile || objectName == skipFileWall5Rot90 || objectName == skipFileMoveWallRot90 || objectName == skipFileWallsousa) {
		shouldDraw = true;
	}
	else if (objectName == skipFileWall1) {
		shouldDraw = StagePos.z < -9 || DrawFlag;
	}
	else if (objectName == skipFileWall2) {
		shouldDraw = StagePos.z < 6 || DrawFlag;
	}
	else if (objectName == skipFileWall3) {
		shouldDraw = StagePos.z < 15 || DrawFlag;
	}
	else if (objectName == skipFileWall4) {
		shouldDraw = StagePos.z < 18 || DrawFlag;
	}
	else if (objectName == skipFileWall6) {
		shouldDraw = StagePos.z < 55 || DrawFlag;
	}
	else if (objectName == skipFileWall1Rot90) {
		shouldDraw = StagePos.z < 6 || DrawFlag;
	}
	else if (objectName == skipFileWall2Rot90) {
		shouldDraw = StagePos.z < 28 || DrawFlag;
	}
	else if (objectName == skipFileWall3Rot90) {
		shouldDraw = StagePos.z < 50 || DrawFlag;
	}
	else if (objectName == skipFileWall4Rot90) {
		shouldDraw = StagePos.z < 55 || DrawFlag;
	}
	return shouldDraw;
}

void Stage::StageObjDraw()
{
	for (int i = 0; i < GetNames.size(); ++i) {
		if (ObjDraw(GetNames[i])) {
			objects[i]->Draw();
		}
	}
}

bool Stage::ObjDraw(const std::string& objectName) const
{
	if (objectName == skipFileWall0) {
		return false;
	}

	bool shouldDraw = false;
	if (objectName == skipFileTile || objectName == skipFileTile2 || objectName == skipFileTile3 || objectName == skipFileWall5Rot90 || objectName == skipFileMoveWallRot90 || objectName == skipFileWallsousa) {
		shouldDraw = true;
	}
	else if (objectName == skipFileWall1) {
		shouldDraw = StagePos.z < -11 || DrawFlag;
	}
	else if (objectName == skipFileWall2) {
		shouldDraw = StagePos.z < 7 || DrawFlag;
	}
	else if (objectName == skipFileWall3) {
		shouldDraw = StagePos.z < 14 || DrawFlag;
	}
	else if (objectName == skipFileWall4) {
		shouldDraw = StagePos.z < 18 || DrawFlag;
	}
	else if (objectName == skipFileWall6) {
		shouldDraw = StagePos.z < 55 || DrawFlag;
	} 
	else if (objectName == skipFileWall7) {
		shouldDraw = StagePos.z > 1 || DrawFlag; 
	}
	else if (objectName == skipFileWall1Rot90) {
		shouldDraw = StagePos.z < 7 || DrawFlag;
	}
	else if (objectName == skipFileWall2Rot90) {
		shouldDraw = StagePos.z < 15 || DrawFlag;
	}
	else if (objectName == skipFileWall3Rot90) {
		shouldDraw = StagePos.z < 50 || DrawFlag;
	}
	else if (objectName == skipFileWall4Rot90) {
		shouldDraw = StagePos.z < 55 || DrawFlag;
	}
	return shouldDraw;
}