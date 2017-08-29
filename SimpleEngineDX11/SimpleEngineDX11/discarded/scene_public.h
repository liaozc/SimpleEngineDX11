#ifndef INTERFACE_PUBLIC_H
#define INTERFACE_PUBLIC_H

#include "pipeline_component_public.h"

class iSceneObject;

class iScene :public iPipelineComponent
{
public:
	virtual void AddObject(iSceneObject* pObj) = 0;
	virtual void RemoveObject(iSceneObject* pObj) = 0;
	virtual void DoRender() = 0;
};

#endif
