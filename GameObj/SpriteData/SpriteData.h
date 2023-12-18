#pragma once
#include"2d/Sprite.h"
#include"2d/SpriteManager.h"
//�X�v���C�g�f�[�^
struct SpriteDatas{
    bool ChangeNum;//�V�[���ύX�ɂ���
    bool BlackNum; //��C�ɈÂ�����̂Ɏg��
    bool SpaceNum; //Space���S
    bool TitleNum; //�^�C�g�����S
    bool SignalNum;//�Q�[���I�[�o�[�Ɏg��
};

class SpriteData
{
public:
    // ������
    void Initialize(SpriteManager* SpriteMan);
    //���t���[������
    void Update();
    //�X�e�[�W�J�E���g
    void SetStageCount(uint32_t Count) { this->StageCount = Count; }
    uint32_t StageCount = 0;

    Sprite* spriteSceneChenge = nullptr;
    Sprite* spriteSPACE = nullptr;
    Sprite* TITLE = nullptr;
    Sprite* Black = nullptr;
    Sprite* Signal = nullptr;
};

