#include "BackObj.h"
#include "Player/Player.h"
#include "Input.h"

BackObj* BackObj::Create(Model* model)
{
    // 3D�I�u�W�F�N�g�̃C���X�^���X�𐶐�
    BackObj* instance = new BackObj();
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

bool BackObj::Initialize()
{
    if (!Object3d::Initialize())
    {
        return false;
    }
    
    return true;
}

void BackObj::Update()
{
    //ToDo�����ύX
    Input* input = Input::GetInstance();
    if (player) {
        Ppos = player->GetPosition();
        count[0] = Ppos.x - position.x;
        count[1] = Ppos.z - position.z;
    }
     // �v���C���[�Ƃ̋������v�Z���A��苗���i�񂾂琶������
        const float distanceThreshold = 1.0f;
        if (abs(Ppos.x - position.x) <= distanceThreshold || abs(Ppos.z - position.z) <= distanceThreshold)
        {
            // �����t���O�𗧂Ă�
            flag = true;
                if (nextBackObj) {
                    nextBackObj->SetPosition(Ppos);
                }
            


        }

    
    rotation = { 90,0,90 };
    Object3d::Update();
}

void BackObj::Draw()
{
    if (flag)
    {
        Object3d::Draw();
    }
}

void BackObj::SetPlayer(Player* player)
{
    this->player = player;
}
void BackObj::NextBackObj(BackObj* next)
{
    this->nextBackObj = next;
}

void BackObj::GetNextBackObjPos(XMFLOAT3 poss)
{
    this->nextBackObj->position = poss;
}
