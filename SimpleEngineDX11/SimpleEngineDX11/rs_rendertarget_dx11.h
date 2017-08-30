#ifndef RS_RT_DX11_H
#define RS_RT_DX11_H

#include <d3d11.h>
#include "rs_rendertarget_public.h"

class RS_RenderTargetDX11 :public iRS_RenderTarget
{
public:
	RS_RenderTargetDX11();
	RS_RenderTargetDX11(ID3D11RenderTargetView**, unsigned, ID3D11DepthStencilView*);

	virtual void UnInit();
	
	ID3D11RenderTargetView** GetRenderTargetView() const { return m_pRenderTargetViews; }
	unsigned GetRenderTargetViewSize() const { return m_nRTViewCount; }
	ID3D11DepthStencilView* GetDepthStencilView() const { return m_pDepthStencilView; }
	
protected:
	ID3D11RenderTargetView** m_pRenderTargetViews;
	unsigned m_nRTViewCount;
	ID3D11DepthStencilView* m_pDepthStencilView;
};

#endif
