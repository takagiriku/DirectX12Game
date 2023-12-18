#include "SpriteData.h"
#include <GameObj/Data/Data.h>

SpriteDatas spriteDatas[StageNum] = {
	{true,false,true,  true, false}, //�^�C�g��
	{true,true, false, false, false},//�X�e�[�W1
	{true,true, false, false, false},//�X�e�[�W2
	{true,true, false, false, false},//�Q�[���N���A
	{true,true,true, false, true}    //�Q�[���I�[�o�[
};

void SpriteData::Initialize(SpriteManager* SpriteMan)
{
	if (spriteDatas[StageCount].SpaceNum)
	{
		SpriteMan->LoadTexture(0, L"Resources/SPACE.png");
		spriteSPACE = new Sprite;
		spriteSPACE->Create(0);
	}
	if (spriteDatas[StageCount].ChangeNum)
	{
		SpriteMan->LoadTexture(1, L"Resources/scenechenge.png");
		spriteSceneChenge = new Sprite;
		spriteSceneChenge->Create(1);
	}
	if (spriteDatas[StageCount].TitleNum)
	{
		SpriteMan->LoadTexture(2, L"Resources/TITLE.png");
		TITLE = new Sprite;
		TITLE->Create(2);
	}
	if (spriteDatas[StageCount].BlackNum)
	{
		SpriteMan->LoadTexture(3, L"Resources/black.png");
		Black = new Sprite;
		Black->Create(3);
	}
	if (spriteDatas[StageCount].SignalNum)
	{
		SpriteMan->LoadTexture(4, L"Resources/No Signal.png");
		Signal = new Sprite;
		Signal->Create(4);
	}
	
}

void SpriteData::Update()
{
}
