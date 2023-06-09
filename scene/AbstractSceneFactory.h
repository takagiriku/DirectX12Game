#pragma once
#include "BaseScene.h"
#include <string>
// �V�[���H��T�O
class AbstractSceneFactory
{
public:
	virtual ~AbstractSceneFactory() = default;

	
	/// �V�[������
	virtual BaseScene* CreateScene(const std::string& sceneName) = 0;
};