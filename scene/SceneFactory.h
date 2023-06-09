#pragma once
#include "AbstractSceneFactory.h"


class SceneFactory :
    public AbstractSceneFactory
{
	/// �V�[������
	BaseScene* CreateScene(const std::string& sceneName) override;
};

