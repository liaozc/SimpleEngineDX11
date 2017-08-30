#ifndef SCENEOBJECT_PUBLIC_H
#define SCENEOBJECT_PUBLIC_H

#include "transform.h"
#include "rs_meshrenderer_public.h"

class SceneObject : Transform
{
public:
	iRS_MeshRenderer* GetMeshRenderer() const { return m_pMeshRenderer; }

protected:
	iRS_MeshRenderer* m_pMeshRenderer;


};

#endif
