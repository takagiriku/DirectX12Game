#pragma once
#include <cstdint>

// �X�e�[�W�f�[�^
struct StageData {
    uint32_t itemNum;
    uint32_t KeyNum;
    uint32_t BoxNum;

};
// �X�e�[�W��
const uint32_t StageNum = 5;

class Data
{
    // ������
    void Initialize();

    // �I��
    void Finalize();

    // ���t���[��
    void Update();

    

};

