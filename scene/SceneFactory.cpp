#include "SceneFactory.h"
#include "TitleScene.h"
#include "NormalStageScene.h"
#include "RandomStageScene.h"
#include"EndScene.h"
#include"ClearScene.h"

BaseScene* SceneFactory::CreateScene(const std::string& sceneName)
{
    //éüÇÃÉVÅ[ÉìÇê∂ê¨
    BaseScene* newScene = nullptr;
    if (sceneName == "TITLE")
    {
        newScene = new TitleScene();
    }
    else if (sceneName == "NORMAL")
    {
        newScene = new NormalStageScene();
    } else if (sceneName == "RANDOM")
    {
        newScene = new RandomStageScene();
    }
    else if (sceneName == "END")
    {
        newScene = new EndScene();
    }
    else if (sceneName == "CLEAR")
    {
        newScene = new ClearScene();
    }

    return newScene;
}
