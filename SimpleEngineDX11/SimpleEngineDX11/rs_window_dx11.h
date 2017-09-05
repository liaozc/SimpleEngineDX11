#ifndef RS_WINDOW_DX11_H
#define RS_WINDOW_DX11_H

#include <d3d11.h>
#include "rs_window_public.h"
#include "rs_renderer_public.h"

class RS_WindowDX11 : public iRS_Window
{
public:
	virtual ~RS_WindowDX11();
	virtual HRESULT Init(HWND hwnd, iRS_Renderer* pRenderer);
	virtual iRS_RenderTarget* GetRenderTarget() const;
	virtual void OnSize(HWND hwnd, unsigned w, unsigned h);
	virtual void Present();
protected:
	HRESULT createRT();
protected:
	int		m_nWidth;
	int		m_nHeight;
	HWND	m_hwnd;
	IDXGISwapChain* m_pSwapChain;
	iRS_RenderTarget* m_pRT;
	ID3D11Texture2D* m_pDepthStencil;
	DXGI_FORMAT m_backBufferFormat;
	iRS_Renderer* m_pRenderer;
	int m_nMSAA;
};

#endif
