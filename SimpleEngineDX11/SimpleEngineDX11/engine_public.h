#ifndef INTERFACE_ENGINE_H
#define INTERFACE_ENGINE_H

#include "platform.h"

//D3D sapce
interface ID3D11Device;

class iRenderTarget;

struct EngineOption
{

};

class iEngine
{

public:
	virtual ID3D11Device* getDevice() const = 0;
public:
	virtual HRESULT addRenderTarget(iRenderTarget* target) = 0;
//	virtual void Render() = 0;
//	virtual iScene* CreateScene(LPCSTR pFilepath = nullptr) = 0;	//file = nullptr时，相当于NewScene
//	virtual void SetActiveScene(iScene* pScene) = 0;

};


#endif
