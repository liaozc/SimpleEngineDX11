#ifndef INTERFACE_PUBLIC_H
#define INTERFACE_PUBLIC_H

class iSceneObject;

class iScene
{
public:
	virtual void AddObject(iSceneObject* pObj) = 0;
	virtual void RemoveObject(iSceneObject* pObj) = 0;

};

#endif
