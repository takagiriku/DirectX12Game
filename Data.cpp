#include "Data.h"
#include"GameObj/Key/Key.h"
#include"GameObj/Battery/Battery.h"
#include"GameObj/Player/Player.h"
#include"GameObj/Player/PlayerHead.h"
#include"GameObj/BlockObj//BlockObj.h"
#include"2d/SpriteManager.h"
//ToDo �f�[�^���܂Ƃ߂�
StageData stageDatas[StageNum] = {
    { 1, 1, 9, 2},// �`���[�g���A��
    { 8, 1, 0, 0},// �X�e�[�W1
    { 4, 1, 0, 0},//�X�e�[�W2
    { 0 ,0, 0, 2},//�N���A�X�e�[�W
    { 0 ,0, 0, 0} //�Q�[���I�[�o�[
};
LightData lightDatas[StageNum] = {
    { 1, 2, 3},// �`���[�g���A��
    { 1, 1, 0},// �X�e�[�W1
    { 1, 1, 0},//�X�e�[�W2
    { 1 ,0, 0},//�N���A�X�e�[�W
    { 1 ,0, 0} //�Q�[���I�[�o�[
};

void Data::Initialize()
{
    mKey = Model::CreateOBJ("key");
    mBattery = Model::CreateOBJ("Battery");
    mDome = Model::CreateOBJ("skydome");
    mPlayerBody = Model::CreateOBJ("playerbody");
    mPlayer = Model::CreateOBJ("playerobj");
    mTitleObjs = Model::CreateOBJ("TitleObjs");
    mTitleMove = Model::CreateOBJ("titleobj");
    mBlockObj = Model::CreateOBJ("Blackobj");
   

    int i = StageCount;

    if (stageDatas[i].KeyNum)
    {
        for (int j = 0; j < stageDatas[i].KeyNum; j++) { Keys[j] = Key::Create(mKey); }
    }
    else
    {
        Keys[i] = nullptr;
    }
    if (stageDatas[i].BatteryNum)
    {
        for (int j = 0; j < stageDatas[i].BatteryNum; j++) { battery[j] = Battery::Create(mBattery); }
    }
    else
    {
        battery[i] = nullptr;
    }
    if (stageDatas[i].TitleObjNum)
    {
        for (int j = 0; j < stageDatas[i].TitleObjNum; j++) { TitleObjs[j] = Object3d::Create(mTitleObjs); }
    }
    else
    {
        TitleObjs[i] = nullptr;
    }
    if (stageDatas[i].TitleMoveNum)
    {
        for (int j = 0; j < stageDatas[i].TitleMoveNum; j++) { TitleMove[j] = Object3d::Create(mTitleMove); }
    }
    else
    {
        TitleMove[i] = nullptr;
    }
    for (int i = 0; i < 10; i++)
    {
        objblock[i] = BlockObj::Create(mBlockObj);
    }
    objPlayerBody = Player::Create(mPlayerBody);
    objPlayer = PlayerHead::Create(mPlayer);
    
    Dome = Object3d::Create(mDome);
    

    // ���C�g����
    light = Light::Create();
    // 3D�I�u�G�N�g�Ƀ��C�g���Z�b�g
    Object3d::SetLightGroup(light);
    if (lightDatas[i].SpotLightNum)
    {
        for (int j = 0; j < lightDatas[i].SpotLightNum; j++) { light->SetSpotLightActive(j, true); }
    }
    if (lightDatas[i].PointLightNum)
    {
        for (int j = 0; j < lightDatas[i].PointLightNum; j++) { light->SetPointLightActive(j, true); }
    }
    if (lightDatas[i].ShadowNum)
    {
        for (int j = 0; j < lightDatas[i].ShadowNum; j++) { light->SetCircleShadowActive(j, true); }
    }
    
}

void Data::Finalize()
{
    safe_delete(Dome);
    safe_delete(mDome);
    safe_delete(mKey);
    safe_delete(mBattery);
    safe_delete(objPlayerBody);
    safe_delete(objPlayer);
    safe_delete(mPlayerBody);
    safe_delete(mPlayer);
    safe_delete(mTitleObjs);    
    safe_delete(mTitleMove);
    safe_delete(mBlockObj);
    safe_delete(light);
    for (int i = 0; i < 10; i++)
    {
        safe_delete(TitleObjs[i]);
        safe_delete(TitleMove[i]);
        safe_delete(Keys[i]);
    }
    for (int i = 0; i < 10; i++)
    {
        safe_delete(objblock[i]);
    }
}

void Data::Update()
{
    int i = StageCount;
}
