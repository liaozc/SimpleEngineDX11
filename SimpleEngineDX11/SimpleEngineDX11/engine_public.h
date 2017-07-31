#ifndef INTERFACE_ENGINE_H
#define INTERFACE_ENGINE_H

#include "platform.h"

class iEngine;
class iWindow;
class iScene;

extern "C" iEngine* CreateSimpleEngine();


class iEngine
{
public:
	virtual iWindow* CreateFromLocalWindow(wndHandle handle) = 0;	//封装本地窗口，用到的本地功能尽量少
	virtual void AddRenderWindow(iWindow* pWnd) = 0;				//多窗口支持扩展，暂时只有一个窗口
	virtual void Render() = 0;
	virtual iScene* CreateScene(LPCSTR pFilepath = nullptr) = 0;	//file = nullptr时，相当于NewScene
	virtual void SetActiveScene(iScene* pScene) = 0;

};


#endif
