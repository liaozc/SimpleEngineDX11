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
	virtual iWindow* CreateFromLocalWindow(wndHandle handle) = 0;	//��װ���ش��ڣ��õ��ı��ع��ܾ�����
	virtual void AddRenderWindow(iWindow* pWnd) = 0;				//�ര��֧����չ����ʱֻ��һ������
	virtual void Render() = 0;
	virtual iScene* CreateScene(LPCSTR pFilepath = nullptr) = 0;	//file = nullptrʱ���൱��NewScene
	virtual void SetActiveScene(iScene* pScene) = 0;

};


#endif
