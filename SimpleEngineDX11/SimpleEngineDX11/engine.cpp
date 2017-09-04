#include "engine.h"
#include "rs_renderer_dx11.h"
#include "geo_manager.h"

static iEngine* g_pEngine = nullptr;

extern "C" DLL_API
iEngine* CreateEngine(const t_EngineConfigOptMap& option)
{
	if (!g_pEngine) {
		g_pEngine = new Engine();
		if (FAILED(g_pEngine->Init(option))) {
			delete g_pEngine;
			g_pEngine = nullptr;
		}
	}
	return g_pEngine;
}

extern "C" DLL_API
void DestructEngine()
{
	if (g_pEngine) {
		g_pEngine->UnInit();
		delete g_pEngine;
		g_pEngine = nullptr;
	}
}

void Engine::init()
{
	m_pRenderer = nullptr;
}

HRESULT Engine::Init(const t_EngineConfigOptMap & option)
{
	init();
	HRESULT hRet = E_FAIL;
	do {
		t_EngineConfigOptMap::const_iterator it = option.find(eECO_RendererType);
		if(it == option.end()) break;

		const std::string& opt_renderer = it->second;
		if (opt_renderer != "dx11")  break;
		m_pRenderer = new RS_RendererDX11();
		if (FAILED(m_pRenderer->Init())) break;
		m_pGeoMger = new GeometryManager();

		hRet = S_OK;
	
	} while (0);

	if (FAILED(hRet))
		UnInit();

	return hRet;
}

void Engine::UnInit()
{
	if (m_pRenderer) {
		m_pRenderer->UnInit();
		delete m_pRenderer;
	}
}

iRS_Renderer * Engine::GetRenderer() const
{
	return m_pRenderer;
}

iGEO_Manager * Engine::GetGeometryManager() const
{
	return m_pGeoMger;
}

