#include "Framework.h"

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{
    for (pair<string, Scene*> scene : scenes)
    {
        delete scene.second;
    }
}

void SceneManager::Update()
{
    for (Scene* scene : activeScenes)
        scene->Update();
}

void SceneManager::PreRender()
{
    for (Scene* scene : activeScenes)
        scene->PreRender();
    
}

void SceneManager::Render()
{
    for (Scene* scene : activeScenes)
        scene->Render();
}

void SceneManager::PostRender()
{
    for (Scene* scene : activeScenes)
        scene->PostRender();
}

void SceneManager::GUIRender()
{
    for (Scene* scene : activeScenes)
        scene->GUIRender();
}

void SceneManager::InfoRender()
{
    for (Scene* scene : activeScenes)
        scene->InfoRender();
}

void SceneManager::UpgradeButton()
{
    for (Scene* scene : activeScenes)
        scene->UpgradeButton();
}


void SceneManager::Create(string key, Scene* scene)
{
    if (scenes.count(key) > 0)
        return;

    scenes[key] = scene;
}

void SceneManager::Add(string key)
{
    if (scenes.count(key) == 0)
        return;

    // °°Àº ¾À ¿¹¿Ü
    for (Scene* scene : activeScenes)
    {
        if (scenes[key] == scene)
            return;
    }

    activeScenes.push_back(scenes[key]);
    activeScenes.back()->Start();

}

void SceneManager::Remove(string key)
{
    for (UINT i = 0; i < activeScenes.size(); i++)
    {
        if (activeScenes[i] == scenes[key])
        {
            scenes[key]->End();
            activeScenes.erase(activeScenes.begin() + i);
            return;
        }
    }
}
