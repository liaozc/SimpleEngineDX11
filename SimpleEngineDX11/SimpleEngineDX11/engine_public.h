#ifndef ENGINE_PUBLIC_H
#define ENGINE_PUBLIC_H

#include "rs_renderer_public.h"
#include "stl_containers.h"
#include <string>
#include "geo_manager_public.h"

class iEngine;
enum eEngineConfigOption
{
	eECO_RendererType,
	eECO_Count,
};
typedef std::map<eEngineConfigOption, std::string> t_EngineConfigOptMap;

extern "C" DLL_API  iEngine* CreateEngine(const t_EngineConfigOptMap& option);
extern "C" DLL_API  void DestructEngine();

typedef iEngine* (* pfnCreateEngineFunc)(const t_EngineConfigOptMap& option);
typedef void(*pfnDestructEngineFunc)();


class iEngine
{
public:
	virtual HRESULT Init(const t_EngineConfigOptMap& option) = 0;
	virtual void	UnInit() = 0;
	virtual iRS_Renderer* GetRenderer() const = 0;
	virtual iGEO_Manager* GetGeometryManager() const = 0;
};

#endif
