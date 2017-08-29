#include "render_target_public.h"
#include "platform.h"

#include <dxgi.h>

class RTWindow : public iRenderTarget
{
public:
	virtual void Init(iEngine* pEngine) ;
	virtual void OnAttached() ;
	virtual void OnDetached() ;
	virtual void BindWndHandle(wndHandle hwnd);
protected:
	iEngine* m_pEngine;
	wndHandle m_hwnd;
	IDXGISwapChain* m_pSwapChain;

};

