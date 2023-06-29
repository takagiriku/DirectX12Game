#include"Stage.h"
#include"GameObj/Player/Player.h"
#include "LevelLoader.h"

Stage::Stage()
{

}

Stage::~Stage()
{
	safe_delete(modelGround);
	safe_delete(modelSpaceWall);
	safe_delete(modelSpaceWall2);
}

void Stage::Initialize()
{

	modelGround = Model::CreateOBJ("tile");
	modelSpaceWall = Model::CreateOBJ("spacewall");
	modelSpaceWall2 = Model::CreateOBJ("spacewall2");


	models.insert(std::make_pair("tile", modelGround));
	models.insert(std::make_pair("tile2", modelGround));
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
	const std::vector<std::string> fileNames = { "Stage0-2blend","Stage1-1-2","Stage2","newStage3","stage3-2" };
	const std::vector<LevelData*>fileDatas = LevelLoader::LoadFile(fileNames);
	for (size_t i = 0; i < fileNames.size(); i++) {
		fileData.insert(std::make_pair(fileNames[i], fileDatas[i]));
	}

	auto it0 = fileData.find("Stage0-2blend");
	auto it = fileData.find("Stage1-1-2");
	auto it2 = fileData.find("Stage2");
	auto it3 = fileData.find("newStage3");
	auto it4 = fileData.find("stage3-2");

	if (GenerationFlag == false)
	{

		if (stagecount == 0)
		{
			if (it0 != fileData.end()) {
				levelData = it0->second;
			}
		}
		if (stagecount == 1)
		{
			if (it != fileData.end()) {
				levelData = it->second;
			}
		}
		else if (stagecount == 2)
		{
			if (it2 != fileData.end()) {
				levelData = it2->second;
			}
		}
		else if (stagecount == 3)
		{
			if (it3 != fileData.end()) {
				levelData = it3->second;
			}
		}else if (stagecount == 4)
		{
			if (it4 != fileData.end()) {
				levelData = it4->second;
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

			if (objectData.fileName == skipFileTile || objectData.fileName == skipFileTile2) {
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
	GenerationFlag = false;
	//前のデータ削除
	for (auto& object : objects) {
		delete object;
	}
	objects.clear();
	GetNames.clear();
}
void Stage::StageObjDraw0()
{
	for (int i = 0; i < GetNames.size(); ++i) {
		if (GetNames[i] == skipFileTile || GetNames[i] == skipFileSlope) {
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
		if (GetNames[i] == skipFileTile || GetNames[i] == skipFileTile2) {
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
void Stage::StageObjDraw2()
{
	for (int i = 0; i < GetNames.size(); ++i) {
		if (GetNames[i] == skipFileTile || GetNames[i] == skipFileSlope) {
			objects[i]->Draw();
		}
		if (GetNames[i] == skipFileWall0) {
			//objects[i]->Draw();
		}
		if (GetNames[i] == skipFileWall1) {
			if (camerapos.z < -10 || DrawFlag)
			{
				objects[i]->Draw();
			}
		}
		if (GetNames[i] == skipFileWall2) {
			if (camerapos.z < 2 || DrawFlag)
			{
				objects[i]->Draw();
			}
		}
		if (GetNames[i] == skipFileWall3) {
			if (camerapos.z < 15 || DrawFlag)
			{
				objects[i]->Draw();
			}
		}
		if (GetNames[i] == skipFileWall4) {
			if (camerapos.z < 18 || DrawFlag)
			{
				objects[i]->Draw();
			}
		}
		if (GetNames[i] == skipFileWall5) {
			if (camerapos.z < 35 || DrawFlag)
			{
				objects[i]->Draw();
			}
		}
		if (GetNames[i] == skipFileWall6) {
			if (camerapos.z < 38 || DrawFlag)
			{
				objects[i]->Draw();
			}
		}if (GetNames[i] == skipFileWall7) {
			if (camerapos.z < 55 || DrawFlag)
			{
				objects[i]->Draw();
			}
		}if (GetNames[i] == skipFileWall8) {
			if (camerapos.z < 55 || DrawFlag)
			{
				objects[i]->Draw();
			}
		}
		if (GetNames[i] == skipFileWall9) {
			objects[i]->Draw();
		}
		if (GetNames[i] == skipFileWall1Rot90) {
			if (camerapos.z < 2 || DrawFlag)
			{
				objects[i]->Draw();
			}
		}
		if (GetNames[i] == skipFileWall2Rot90) {
			if (camerapos.z < 20 || DrawFlag)
			{
				objects[i]->Draw();
			}
		}
		if (GetNames[i] == skipFileWall3Rot90) {
			if (camerapos.z < 38 || DrawFlag)
			{
				objects[i]->Draw();
			}
		}
		if (GetNames[i] == skipFileWall4Rot90) {
			if (camerapos.z < 55 || DrawFlag) {
				objects[i]->Draw();
			}
		}
		if (GetNames[i] == skipFileWall5Rot90) {
			objects[i]->Draw();
		}
		if (GetNames[i] == skipFileMoveWallRot90) {
			objects[i]->Draw();
		}
	}
}
