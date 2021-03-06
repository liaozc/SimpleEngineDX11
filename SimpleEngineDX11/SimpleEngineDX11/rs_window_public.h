#ifndef RS_WINDOW_PUBLIC_H
#define RS_WINDOW_PUBLIC_H

#include "ref_public.h"

class iRS_Renderer;
class iRS_RenderTarget;

class iRS_Window : public iRef
{
public:
	virtual ~iRS_Window() {}
	virtual HRESULT Init(HWND hwnd,iRS_Renderer* pRenderer) = 0;
	virtual iRS_RenderTarget* GetRenderTarget() const = 0;
	virtual void OnSize(HWND hwnd, unsigned w, unsigned h) = 0;
	virtual void Present() = 0;
};

#endif
