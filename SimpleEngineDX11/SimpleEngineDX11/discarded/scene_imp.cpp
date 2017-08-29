#include "scene_imp.h"



extern "C" 
iScene* CreateScene(iEngine* pEngine)
{
	Scene* pScene = new Scene();
	pScene->Init(pEngine);
	return pScene;
}

Scene::Scene():
	m_pEngine(nullptr)
{
}

void Scene::Init(iEngine * pEngine)
{
	m_pEngine = pEngine;
}

void Scene::OnAttached()
{

}

void Scene::OnDetached()
{
}

void Scene::AddObject(iSceneObject * pObj)
{
}

void Scene::RemoveObject(iSceneObject * pObj)
{
}

void Scene::DoRender()
{
}
