#include "Data.h"
#include"GameObj/Key/Key.h"
#include"GameObj/Battery/Battery.h"
#include"GameObj/Box/Box.h"
#include"GameObj/Backobj/Backobj.h"
#include"GameObj/Player/Player.h"
#include"GameObj/Player/PlayerHead.h"
#include"GameObj/Tile/Tile.h"

//ToDo �f�[�^���܂Ƃ߂�
StageData stageDatas[StageNum] = {
    { 1, 1, 0}, // �`���[�g���A��
    { 8, 1, 0}, // �X�e�[�W1
    { 4, 1, 4 },//�X�e�[�W2
    { 0 ,0, 0},//�N���A�X�e�[�W
    { 0 ,0, 0}//�Q�[���I�[�o�[
};

void Data::Initialize()
{
    mKey = Model::CreateOBJ("key");
    mBattery = Model::CreateOBJ("Battery");
    mBox = Model::CreateOBJ("Box");

    int i = StageCount;

    if (stageDatas[i].KeyNum)
    {
        for (int j = 0; j < stageDatas[i].KeyNum; j++) {
            Keys[j] = Key::Create(mKey);
        }
    }
    else
    {
        Keys[i] = nullptr;
    }
    if (stageDatas[i].itemNum)
    {
        for (int j = 0; j < stageDatas[i].itemNum; j++) {
            battery[j] = Battery::Create(mBattery);
        }
    }
    else
    {
        battery[i] = nullptr;
    }
    if (stageDatas[i].BoxNum)
    {
        for (int j = 0; j < stageDatas[i].BoxNum; j++) {
            box[j] = Box::Create(mBattery);
        }
    }
    else
    {
        box[i] = nullptr;
    }

        
    
}

void Data::Finalize()
{
}

void Data::Update()
{
}
