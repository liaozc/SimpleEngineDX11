#ifndef INTERFACE_ENGINE_H
#define INTERFACE_ENGINE_H

#include "platform.h"
#include "stl_containers.h"


class iRenderer;
class iRenderTarget;
class iScene;
class iView;

enum eEngineOption {
	eEOPT_RendererType,
	eEOPT_Count,
};

typedef std::map<eEngineOption, std::string> T_EngineOptionMap;

class iEngine
{
public:
	virtual iRenderer* GetRenderer() const = 0;
	virtual iScene*	CreateScene() const = 0;
public:
	virtual int Init(const T_EngineOptionMap& eOptMap) = 0;
		

};


#endif

/* what client tend to do ?

	iEngine* pEngine = CreateEngine(opt);
	iRenderer* pRenderer = pEngine->GetRenderer();
	iRnederTarget* pRT_Wnd = pRenderer->CreateRenderTargetFromHwnd(hwnd);
	iRenderTarget* pRT_Depth = pRenderer->CreateDepthStencil();
	pRenderer->SetRenderTarget(&pRT_Wnd,1,nullptr,pRT_Depth,true);
	iScene* pScene = pEngine->CreateScene();
	pScene->LoadFromFile("...");

	pScene->DoRender_Forward(pRenderer); 
	[
		pRenderer->SetViewPort(m_pViewPort);
		objs = pScene->GetObjectsFromViewPort(pRenderer->GetViewPort());
		lits = pScene->GetLightsFromViewPort(pRenderer->GetViewPort());
		generate_shadow(lits);
		for(; all obj in the objs;)
			obj->DoRender_Forward(pRenderer);
	]
	/
	pScene->DoRender_Deffered(pRenderer)
	[
		pRenderer->SetViewPort(m_pViewPort);
		objs = pScene->GetObjectsFromViewPort(pRenderer->GetViewPort());
		lits = pScene->GetLightsFromViewPort(pRenderer->GetViewPort());
		generate_shadow(lits);
		pRenderer->SetRenderTarget(&pRT_geo,1,nullptr,pRT_Depth,fasle);
		for(; all obj in the objs;)
			obj->DoRender_Deffered(pRenderer);
		for(; all lit in lits;)
			lit->DoLight_Deffered(pRenderer);
		pRenderer->ChangeToMainBuffer();
		pRenderer->Draw(vb_post);
	]
	pRenderer->Present();
	
*/