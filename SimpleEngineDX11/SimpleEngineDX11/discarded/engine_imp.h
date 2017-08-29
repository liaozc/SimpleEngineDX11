#ifndef ENGINE_IMP_H
#define ENGINE_IMP_H

#include <d3d11.h>
#include "engine_public.h"
#include "renderTarget_public.h"
#include "stl_containers.h"

class EngineDX11 : public iEngine
{
	friend iEngine* CreateSimpleEngine(EngineOption& option);
public:
	virtual ID3D11Device* getDevice() const;
	virtual HRESULT addRenderTarget(iRenderTarget* target);
protected:
	bool init(EngineOption&);
	bool create3DDevice(EngineOption&);
protected:
	ID3D11Device* m_pD11Device;
	ID3D11DeviceContext* m_pD11DirectContext;
	std::vector<iRenderTarget*> m_renderTarget;
};

#endif