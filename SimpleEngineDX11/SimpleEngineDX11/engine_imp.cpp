#include "engine_imp.h"

static EngineDX11* g_pEngine = nullptr;
extern "C"
iEngine* CreateSimpleEngine(EngineOption& option)
{
	if (!g_pEngine) {
		g_pEngine = new EngineDX11();
		g_pEngine->init(option);
	}
	return g_pEngine;
}

ID3D11Device * EngineDX11::getDevice() const
{
	return m_pD11Device;
}

bool EngineDX11::init(EngineOption &option)
{
	create3DDevice(option);
	return true;
}

bool EngineDX11::create3DDevice(EngineOption &option)
{
	return true;
}
