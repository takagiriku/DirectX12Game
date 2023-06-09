#pragma once
#include "AbstractSceneFactory.h"


class SceneFactory :
    public AbstractSceneFactory
{
	/// シーン生成
	BaseScene* CreateScene(const std::string& sceneName) override;
};

