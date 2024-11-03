#include "RandomStageScene.h"
#include"GameObj/Player/Player.h"
#include"GameObj/Player/PlayerHead.h"
#include"GameObj/BlockObj//BlockObj.h"
#include"SceneManager.h"
#include <base/SafeDelete.h>
#include"GameObj/Data/Data.h"
#include"GameObj/SpriteData/SpriteData.h"
void RandomStageScene::Initialize(DirectXCommon* dxCommon, Input* input, InputCamera* inputCamera, DebugText* text, PostEffect* post, SpriteManager* SpriteMan, Audio* audio)
{
    BaseScene::Initialize(dxCommon, input, inputCamera, text, post, SpriteMan, audio);

    data = new Data();
    data->SetStageCount(2);
    data->Initialize();

    spriteData = new SpriteData;
    spriteData->SetStageCount(2);
    spriteData->Initialize(SpriteMan);

    particleMan = ParticleManager::Create(dxCommon->GetDevice(), inputCamera);
    Object3d::SetCamera(inputCamera);

    data->objPlayerBody->SetStartFlag(true);
    data->objPlayer->SetStartFlag(true);

    for (int i = 0; i < 10; i++)
    {
        data->battery[i]->SetPosition(BatteryPosition[i]);
    }

    data->Keys[0]->SetPosition(KeyPosition);

    stage = new Stage();
    stage->Initialize();

    inputCamera->SetTarget(CameraPosition);
    inputCamera->SetDistance(3.0f);
    inputCamera->SetEye(XMFLOAT3(Eye));

    post->SetStartFlag(true);
    post->ResetTime();
}

void RandomStageScene::Finalize()
{
    safe_delete(particleMan);
    safe_delete(stage);
    data->Finalize();
}

void RandomStageScene::Update()
{
    PBodyPosition = data->objPlayerBody->GetPosition();

    CameraPosition.x = PBodyPosition.x;
    CameraPosition.y = PBodyPosition.y + 5;
    CameraPosition.z = PBodyPosition.z - 15;
    inputCamera->SetTarget(CameraPosition);
    inputCamera->SetEye(XMFLOAT3(Eye));
    inputCamera->Update();

    if (data->Keys[0]->KeyFlag && abs(PBodyPosition.x - stage->Gole.x) <= 5 && PBodyPosition.y > 10 && PBodyPosition.z > 73)
    {
        data->objPlayerBody->SetMoveFlags(false);
        data->objPlayer->SetMoveFlags(false);
        if (SpriteX[0] < 1280)
        {
            SpriteX[0] += 12.8;
            SpriteY[0] += 7.4;
        }
        if (SpriteX[0] > 1270)
        {
            stage->StageChange();
            post->ResetTime();
            SceneManager::GetInstance()->ChangeScene("END");
        }
    }
    else
    {
        if (SpriteX[0] > 0)
        {
            SpriteX[0] -= 12.8;
            SpriteY[0] -= 7.4;
        }
    }
    Time[0] = post->Time;

    float speed = 0.005;
    AlphaFlag = post->Time > 170;

    if (AlphaFlag)
    {
        if (alpha[0] < 1)
        {
            alpha[0] += speed;
        }
    }
    else
    {
        if (alpha[0] > 0.005)
        {
            alpha[0] -= speed;
        }
    }
    if (alpha[0] > 1)
    {
        stage->StageChange();
        post->ResetTime();
        SceneManager::GetInstance()->ChangeScene("END");
    }
    particleMan->Update();
    spriteData->Black->SetAlpha(alpha[0]);
    spriteData->spriteSceneChenge->SetPosition({ 640 - SpriteX[0], 360 - SpriteY[0] });
    spriteData->spriteSceneChenge->SetSize({ SpriteX[0] * 2.0f, SpriteY[0] * 2.0f });

    stage->Stage1();
    stage->GetCameraPos(CameraPosition);
    stage->SetKeyFlag(data->Keys[0]->KeyFlag);
    data->Update(post, particleMan);
}

void RandomStageScene::Draw()
{
    ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
    Object3d::PreDraw(cmdList);
    data->objPlayerBody->Draw();
    data->objPlayer->Draw();
    data->Keys[0]->Draw();
    for (int i = 0; i < 10; i++)
    {
        data->battery[i]->Draw();
    }
    stage->StageObjDraw();
    data->Dome->Draw();
    particleMan->Draw(cmdList);
    Object3d::PostDraw();
}

void RandomStageScene::Draw2D()
{
    ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
    Sprite::PreDraw(cmdList);
    spriteData->spriteSceneChenge->Draw();
    Sprite::PostDraw();
}

void RandomStageScene::FirstDraw2D()
{
    ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
    Sprite::PreDraw(cmdList);
    spriteData->Black->Draw();
    Sprite::PostDraw();
}

void RandomStageScene::DrawImGui()
{
	ImGui::Begin("pos");
	ImGui::SetWindowPos(ImVec2(0, 0));
	ImGui::SetWindowSize(ImVec2(500, 200));
	ImGui::InputFloat("al", alpha);
	ImGui::InputFloat("time", Time);
	ImGui::InputFloat3("Player", data->objPlayer->ppos);
	ImGui::End();
}