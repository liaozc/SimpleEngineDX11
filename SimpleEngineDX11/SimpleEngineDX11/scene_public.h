#ifndef SCENE_PUBLIC_H
#define SCENE_PUBLIC_H

class iSceneObject;
class iRS_Renderer;

class iRS_Scene 
{
public:
	virtual void AddObj(iSceneObject* pObj) = 0;
	virtual void RemObj(iSceneObject* pObj) = 0;
	virtual void DoRender(iRS_Renderer* pRenderer) = 0;
};

#endif