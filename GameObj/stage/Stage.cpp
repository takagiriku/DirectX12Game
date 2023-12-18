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
	// モデルの解放
	safe_delete(modelGround);
	safe_delete(modelSpaceWall);
	safe_delete(modelSpaceWall2);

	// 生成したオブジェクトの解放
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


		// レベルデータからオブジェクトを生成、配置
		for (auto& objectData : levelData->objects) {
			// ファイル名から登録済みモデルを検索
			Model* model = nullptr;
			decltype(models)::iterator it = models.find(objectData.fileName);
			if (it != models.end()) {
				model = it->second;
			}

			// モデルを指定して3Dオブジェクトを生成
			Object3d* newObject;

			if (objectData.fileName == skipFileTile || objectData.fileName == skipFileTile2 || objectData.fileName == skipFileTile3) {
				newObject = TouchableObject::Create(model);
			}
			else {
				newObject = Object3d::Create(model);
			}

			// 座標
			DirectX::XMFLOAT3 pos;
			DirectX::XMStoreFloat3(&pos, objectData.translation);
			newObject->SetPosition(pos);

			// 回転角
			DirectX::XMFLOAT3 rot;
			DirectX::XMStoreFloat3(&rot, objectData.rotation);
			newObject->SetRotation(rot);

			// サイズ
			DirectX::XMFLOAT3 scale;
			DirectX::XMStoreFloat3(&scale, objectData.scaling);
			newObject->SetScale(scale);

			
			// 配列に登録
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
				float MoveY = Position.y + speed; // 一定の速度で動く
				Gole = Position;

				if (MoveY < MaxPos)
				{
					objects[i]->SetPosition({ Position.x, MoveY, Position.z });
				}
				else if (BoxCount == 2)
				{
					MaxPos = 0; // MaxPosを0に設定

					if (MoveY > MaxPos)
					{
						MoveY -= speed; // 一定の速度で下に移動
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
	// 生成したオブジェクトの解放
	for (auto& object : objects) {
		delete object;
	}
	objects.clear();
	GetNames.clear();
}
void Stage::StageObjDraw0()
{
	for (int i = 0; i < GetNames.size(); ++i) {
		if (GetNames[i] == skipFileTile) {
			objects[i]->Draw();
		}
		if (GetNames[i] == skipFileWall0) {
			//objects[i]->Draw();
		}
		if (GetNames[i] == skipFileWall1) {
			if (StagePos.z < -9 || DrawFlag)
			{
				objects[i]->Draw();
			}

		}
		if (GetNames[i] == skipFileWall2) {
			if (StagePos.z < 6 || DrawFlag)
			{
				objects[i]->Draw();
			}
		}
		if (GetNames[i] == skipFileWall3) {
			if (StagePos.z < 15 || DrawFlag)
			{
				objects[i]->Draw();
			}
		}
		if (GetNames[i] == skipFileWall4) {
			if (StagePos.z < 18 || DrawFlag)
			{
				objects[i]->Draw();
			}
		}
		if (GetNames[i] == skipFileWall5) {
			if (StagePos.z < 50 || DrawFlag)
			{
				objects[i]->Draw();
			}
		}
		if (GetNames[i] == skipFileWall6) {
			if (StagePos.z < 55 || DrawFlag)
			{
				objects[i]->Draw();
			}
		}

		if (GetNames[i] == skipFileWall1Rot90) {
			if (StagePos.z < 6 || DrawFlag)
			{
				objects[i]->Draw();
			}
		}
		if (GetNames[i] == skipFileWall2Rot90) {
			if (StagePos.z < 28 || DrawFlag)
			{
				objects[i]->Draw();
			}
		}
		if (GetNames[i] == skipFileWall3Rot90) {
			if (StagePos.z < 50 || DrawFlag)
			{
				objects[i]->Draw();
			}
		}
		if (GetNames[i] == skipFileWall4Rot90) {
			if (StagePos.z < 55 || DrawFlag) {
				objects[i]->Draw();
			}
		}
		if (GetNames[i] == skipFileWall5Rot90) {
			objects[i]->Draw();
		}
		if (GetNames[i] == skipFileMoveWallRot90) {
			objects[i]->Draw();
		}
		if (GetNames[i] == skipFileWallsousa) {
			objects[i]->Draw();
		}

	}
}

void Stage::StageObjDraw()
{

	for (int i = 0; i < GetNames.size(); ++i) {
		if (GetNames[i] == skipFileTile || GetNames[i] == skipFileTile2 || GetNames[i] == skipFileTile3) {
			objects[i]->Draw();
		}
		if (GetNames[i] == skipFileWall0) {
			//objects[i]->Draw();
		}
		if (GetNames[i] == skipFileWall1) {
			if (StagePos.z < -11 || DrawFlag)
			{
				objects[i]->Draw();
			}
		}
		if (GetNames[i] == skipFileWall2) {
			if (StagePos.z < 7 || DrawFlag)
			{
				objects[i]->Draw();
			}
		}
		if (GetNames[i] == skipFileWall3) {
			if (StagePos.z < 14 || DrawFlag)
			{
				objects[i]->Draw();
			}
		}
		if (GetNames[i] == skipFileWall4) {
			if (StagePos.z < 18 || DrawFlag)
			{
				objects[i]->Draw();
			}
		}
		if (GetNames[i] == skipFileWall5) {
			if (StagePos.z < 40 || DrawFlag)
			{
				objects[i]->Draw();
			}
		}
		if (GetNames[i] == skipFileWall6) {
			if (StagePos.z < 55 || DrawFlag)
			{
				objects[i]->Draw();
			}
		}
		if (GetNames[i] == skipFileWall7) {
			objects[i]->Draw();
		}
		if (GetNames[i] == skipFileWall1Rot90) {
			if (StagePos.z < 7 || DrawFlag)
			{
				objects[i]->Draw();
			}
		}
		if (GetNames[i] == skipFileWall2Rot90) {
			if (StagePos.z < 15 || DrawFlag)
			{
				objects[i]->Draw();
			}
		}
		if (GetNames[i] == skipFileWall3Rot90) {
			if (StagePos.z < 50 || DrawFlag)
			{
				objects[i]->Draw();
			}
		}
		if (GetNames[i] == skipFileWall4Rot90) {
			if (StagePos.z < 55 || DrawFlag) {
				objects[i]->Draw();
			}
		}
		if (GetNames[i] == skipFileWall5Rot90) {
			objects[i]->Draw();
		}
		if (GetNames[i] == skipFileMoveWallRot90) {
			objects[i]->Draw();
		}
		if (GetNames[i] == skipFileWallsousa) {
			objects[i]->Draw();
		}
		
	}
}
