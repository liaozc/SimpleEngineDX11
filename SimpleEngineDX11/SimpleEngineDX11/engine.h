#ifndef ENGINE_H
#define ENGINE_H

#include "engine_public.h"

class Engine : public iEngine
{
public:
	virtual HRESULT Init(const t_EngineConfigOptMap& option);
	virtual void	UnInit();
	virtual iRS_Renderer* GetRenderer() const;
	virtual iGEO_Manager* GetGeometryManager() const;
protected:
	void init();
	iRS_Renderer* m_pRenderer;
	iGEO_Manager* m_pGeoMger;
};


#endif
