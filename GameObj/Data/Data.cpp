#include "Data.h"
#include"GameObj/Key/Key.h"
#include"GameObj/Battery/Battery.h"
#include"GameObj/Player/Player.h"
#include"GameObj/Player/PlayerHead.h"
#include"GameObj/BlockObj//BlockObj.h"
#include"ParticleManager.h"
#include"PostEffect.h"
#include"2d/SpriteManager.h"
//�f�[�^���܂Ƃ߂�
StageData stageDatas[StageNum] = {
    //�o�b�e���[�@�L�[�@�^�C�g���@�����^�C�g���@�����_���u���b�N
    { 1, 1, 9, 2, 0},// �`���[�g���A��
    { 8, 1, 0, 0 , 0},// �X�e�[�W1
    { 4, 1, 0, 0 , 10},//�X�e�[�W2
    { 0 ,0, 0, 2 , 0},//�N���A�X�e�[�W
    { 0 ,0, 0, 0 , 0} //�Q�[���I�[�o�[
};

LightData lightDatas[StageNum] = {
    //�X�|�b�g�@�|�C���g�@�e
    { 1, 2, 3},// �`���[�g���A��
    { 1, 8, 9},// �X�e�[�W1
    { 1, 4, 5},//�X�e�[�W2
    { 1 ,1, 1},//�N���A�X�e�[�W
    { 0 ,0, 0} //�Q�[���I�[�o�[
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
   

    objPlayerBody = Player::Create(mPlayerBody);
    objPlayerBody->SetScale({ 1.5,1.5,1.5 });
    objPlayerBody->SetMoveFlags(true);
    objPlayer = PlayerHead::Create(mPlayer);
    objPlayer->SetScale({ 1.5,1.5,1.5 });
    objPlayer->SetPlayer(objPlayerBody);
    objPlayer->SetMoveFlags(true);

    for (int j = 0; j < stageDatas[StageCount].KeyNum; j++) {
        Keys[j] = Key::Create(mKey);
        Keys[j]->SetScale({ 5,5,5 });
    }
    for (int j = 0; j < stageDatas[StageCount].BatteryNum; j++) {
        battery[j] = Battery::Create(mBattery);
        battery[j]->SetScale({ 1.5,1.5,1.5 });
    }
    for (int j = 0; j < stageDatas[StageCount].TitleObjNum; j++) {
        TitleObjs[j] = Object3d::Create(mTitleObjs);
        TitleObjs[j]->SetRotation({ 0,180,0 });
        TitleObjs[j]->SetPosition({ -12 + j * 3.f,55,-2 });
    }

     for (int j = 0; j < stageDatas[StageCount].TitleMoveNum; j++) { 
         TitleMove[j] = Object3d::Create(mTitleMove); 
         TitleMove[j]->SetScale({ 1.5,1.5,1.5 });
     }
     for (int j = 0; j < stageDatas[StageCount].RandBlockNum; j++) { 
         objblock[j] = BlockObj::Create(mBlockObj); 
         objblock[j]->SetPlayer(objPlayerBody);
     }


    Dome = Object3d::Create(mDome);
    Dome->SetScale({ 3,3,3 });
    Dome->SetPosition({ 180,0,0 });
    // ���C�g����
    light = Light::Create();
    // 3D�I�u�G�N�g�Ƀ��C�g���Z�b�g
    Object3d::SetLightGroup(light);
    if (lightDatas[StageCount].SpotLightNum)
    {
        for (int j = 0; j < lightDatas[StageCount].SpotLightNum; j++) { light->SetSpotLightActive(j, true); }
    }
    if (lightDatas[StageCount].PointLightNum)
    {
        for (int j = 0; j < lightDatas[StageCount].PointLightNum; j++) { light->SetPointLightActive(j, true); }
    }
    if (lightDatas[StageCount].ShadowNum)
    {
        for (int j = 0; j < lightDatas[StageCount].ShadowNum; j++) { light->SetCircleShadowActive(j, true); }
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

void Data::Update(PostEffect* post, ParticleManager* particleMan)
{
   objPlayerBody->Update(light);
   objPlayer->Update();
   Dome->Update();
   light->Update();
   for (int j = 0; j < stageDatas[StageCount].TitleObjNum; j++) { TitleObjs[j]->Update(); }
   for (int j = 0; j < stageDatas[StageCount].TitleMoveNum; j++) { TitleMove[j]->Update(); }
   for (int j = 0; j < stageDatas[StageCount].RandBlockNum; j++) {
       objblock[j]->Update();
   }
   for (int j = 0; j < stageDatas[StageCount].KeyNum; j++) {
       Keys[j]->Update(particleMan, light);
       Keys[j]->SetPos(objPlayerBody->GetPosition());
   }
   for (int j = 0; j < stageDatas[StageCount].BatteryNum; j++) {
       battery[j]->Update(particleMan, post, light, j + 1);
       battery[j]->SetPos(objPlayerBody->GetPosition());
   }
}
