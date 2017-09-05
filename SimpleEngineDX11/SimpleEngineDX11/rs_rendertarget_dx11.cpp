#include "rs_rendertarget_dx11.h"

RS_RenderTargetDX11::RS_RenderTargetDX11():
	m_pRenderTargetViews(nullptr),
	m_nRTViewCount(0),
	m_pDepthStencilView(nullptr)
{

}

RS_RenderTargetDX11::RS_RenderTargetDX11(ID3D11RenderTargetView ** pRTs, unsigned nSize, ID3D11DepthStencilView * pDS,int width,int height)
{
	for (unsigned int i = 0; i < m_nRTViewCount; ++i) {
		SAFE_RELEASE(m_pRenderTargetViews[i]);
	}
	SAFE_RELEASE(m_pDepthStencilView);
	SAFE_DELETE_ARRAY(m_pRenderTargetViews);

	m_pRenderTargetViews = pRTs;
	m_nRTViewCount = nSize;
	m_pDepthStencilView = pDS;
	for (unsigned int i = 0; i < m_nRTViewCount; ++i) {
		SAFE_ADDREF(m_pRenderTargetViews[i]);
	}
	SAFE_ADDREF(m_pDepthStencilView);
	setupViewPort(width,height);
}

RS_RenderTargetDX11::~RS_RenderTargetDX11()
{
	for (unsigned i = 0; i < m_nRTViewCount; ++i) {
		SAFE_RELEASE(m_pRenderTargetViews[i]);
	}
	SAFE_RELEASE(m_pDepthStencilView);
	SAFE_DELETE_ARRAY(m_pRenderTargetViews);
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