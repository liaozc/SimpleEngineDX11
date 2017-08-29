#ifndef RENDER_PUBLIC_H
#define RENDER_PUBLIC_H 

#include "platform.h"
//iRender for dx11 or ogl
//interface are sorted into 3 types. type of control res, type of control context and type of draw and dispatch
//it is inspired by design of dx11.

class iRenderTarget;
class iViewPort;

class iRenderer
{
public:
	//Res.
	//virtual ITexture* CreateTexture2D() = 0;
	//virtual IVertBuffer* CreateVertBuffer() = 0;

	//Control.
	virtual iRenderTarget* CreateRenderTarget() const = 0;
	virtual iRenderTarget* CreateRenderTargetFromHwnd(wndHandle hwnd) const = 0;
	virtual int SetRenderTargets(iRenderTarget* pColors[],unsigned size, iRenderTarget* pDepth,bool bSavedAsMainBuffer = false) = 0;
	virtual int ClearRenderTarget() = 0;
	virtual int ChangeToMainBuffer() = 0;
	//Draw or Dispatch
	virtual int Draw() = 0;

	virtual int Present() = 0;
};


#endif
