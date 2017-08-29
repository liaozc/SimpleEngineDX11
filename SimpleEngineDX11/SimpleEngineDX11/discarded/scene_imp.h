#ifndef SCENE_IMP_H
#define SCENE_IMP_H

#include "scene_public.h"

class Scene : public iScene
{
public:
	Scene();
	//pipelinecomponent
	virtual void Init(iEngine* pEngine);
	virtual void OnAttached();
	virtual void OnDetached();
	//scene 
	virtual void AddObject(iSceneObject* pObj);
	virtual void RemoveObject(iSceneObject* pObj);
	virtual void DoRender();
protected:
	iEngine* m_pEngine;
};

#endif