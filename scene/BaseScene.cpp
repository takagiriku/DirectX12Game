#include "BaseScene.h"
#include <cassert>
BaseScene::BaseScene()
{
}

void BaseScene::Initialize(DirectXCommon* dxCommon, Input* input, InputCamera* inputCamera, DebugText* text, PostEffect* post, SpriteManager* SpriteMan, Audio* audio)
{
	assert(dxCommon);
	assert(input);
	assert(inputCamera);
	assert(text);
	assert(post);
	assert(SpriteMan);
	assert(audio);
	this->dxCommon = dxCommon;
	this->input = input;
	this->inputCamera = inputCamera;
	this->text = text;
	this->post = post;
	this->SpriteMan = SpriteMan;
	this->audio = audio;
}