#pragma once
#include "AbstractSceneFactory.h"


class SceneFactory :
    public AbstractSceneFactory
{
	/// ÉVÅ[Éìê∂ê¨
	BaseScene* CreateScene(const std::string& sceneName) override;
};

