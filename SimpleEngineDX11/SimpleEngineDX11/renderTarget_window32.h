#include "renderTarget_public.h"
#include "platform.h"

#include <dxgi.h>

class RTWindow : public iRenderTarget
{
public:
	virtual void init(iEngine* pEngine);
	virtual void doRender();
	virtual void bindWndHandle(wndHandle hwnd);
protected:
	iEngine* m_pEngine;
	wndHandle m_hwnd;
	IDXGISwapChain* m_pSwapChain;

};

