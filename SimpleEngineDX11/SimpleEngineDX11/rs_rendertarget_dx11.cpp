#include "rs_rendertarget_dx11.h"

RS_RenderTargetDX11::RS_RenderTargetDX11():
	m_pRenderTargetViews(nullptr),
	m_nRTViewCount(0),
	m_pDepthStencilView(nullptr)
{

}

RS_RenderTargetDX11::RS_RenderTargetDX11(ID3D11RenderTargetView ** pRTs, unsigned nSize, ID3D11DepthStencilView * pDS,int width,int height)
{
	m_pRenderTargetViews = pRTs;
	m_nRTViewCount = nSize;
	m_pDepthStencilView = pDS;
	setupViewPort(width,height);
}

void RS_RenderTargetDX11::UnInit()
{
	if (m_pRenderTargetViews && m_nRTViewCount != 0) {
		for (unsigned i = 0; i < m_nRTViewCount; ++i) {
			if (m_pRenderTargetViews[i])
				m_pRenderTargetViews[i]->Release();
		}
		delete[]m_pRenderTargetViews;
		m_pRenderTargetViews = nullptr;
		m_nRTViewCount = 0;
	}
	if (m_pDepthStencilView) {
		m_pDepthStencilView->Release();
		m_pDepthStencilView = nullptr;
	}
}

void RS_RenderTargetDX11::setupViewPort(int width, int height)
{
	m_viewport.TopLeftX = 0;
	m_viewport.TopLeftY = 0;
	m_viewport.MinDepth = 0;
	m_viewport.MaxDepth = 1;
	m_viewport.Width = (float)width;
	m_viewport.Height = (float)height;
}