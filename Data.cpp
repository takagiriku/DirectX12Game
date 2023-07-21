#include "Data.h"

//ToDo データをまとめる
StageData stageDatas[StageNum] = {
    { 1, 1}, // チュートリアル
    { 8, 1}, // ステージ1
    { 4, 1, 4 },//ステージ2
    { 0 ,0},//クリアステージ
    { 0 ,0}//ゲームオーバー
};

void Data::Initialize()
{
}

void Data::Finalize()
{
}

void Data::Update()
{
}
