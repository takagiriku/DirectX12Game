#include "SceneFactory.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "GameScene2.h"
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
    else if (sceneName == "GAME")
    {
        newScene = new GameScene();
    } else if (sceneName == "GAME2")
    {
        newScene = new GameScene2();
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
