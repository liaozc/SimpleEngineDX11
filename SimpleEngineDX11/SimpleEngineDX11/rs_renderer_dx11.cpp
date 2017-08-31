#include "rs_renderer_dx11.h"
#include "rs_buffer_dx11.h"
#include "rs_shader_dx11.h"
#include "rs_texture_dx11.h"
#include "rs_window_dx11.h"
#include "rs_rt_dx11.h"

HRESULT RS_RendererDX11::Init()
{
	m_pDevice = nullptr;
	m_pContext = nullptr;
	D3D_FEATURE_LEVEL featureLevels[] = 
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};
	D3D_FEATURE_LEVEL successFeaturel;
	if (FAILED(D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE, 0, D3D11_CREATE_DEVICE_SINGLETHREADED | D3D11_CREATE_DEVICE_DEBUG, featureLevels, 2,
		D3D11_SDK_VERSION, &m_pDevice, &successFeaturel, &m_pContext))){
		printf("init Renderer fails \n");
		return E_FAIL;
	}
	return S_OK;

}

void RS_RendererDX11::UnInit()
{

	if (m_pContext) {
		m_pContext->ClearState();
		m_pContext->Release();
		m_pContext = nullptr;
	}

	if (m_pDevice) {
		m_pDevice->Release();
		m_pDevice = nullptr;
	}

}

iRS_Texture * RS_RendererDX11::CreateTexture2D(int width, int height, eRS_ResourceFormat format, void * data)
{
	return nullptr;
}

iRS_Texture * RS_RendererDX11::CreateTexture2DFromeFile(LPCSTR pFilePath)
{
	return nullptr;
}

iRS_Buffer * RS_RendererDX11::CreateVertBuffer(eRS_BufferType bufferType, int size, void * data)
{
	RS_BufferDX11* pBuffer = new RS_BufferDX11(bufferType, size, this);
}

iRS_Buffer * RS_RendererDX11::CreateIndexBuffer(int size, void * data)
{
	return nullptr;
}

iRS_Shader * RS_RendererDX11::CreateVShaderFromFile(LPCSTR pFilePath)
{
	return nullptr;
}

iRS_Shader * RS_RendererDX11::CreateVShaderFromMemory(byte * pMemory)
{
	return nullptr;
}

iRS_Window * RS_RendererDX11::CreateWindowFromHandle(HWND hwnd)
{
	RS_WindowDX11 * pWnd = new RS_WindowDX11();
	if (FAILED(pWnd->Init(hwnd,this))) {
		printf("error -> CreateWindowFromHandle \n");
		delete pWnd;
		pWnd = nullptr;
	}
	return pWnd;
}

void RS_RendererDX11::DestoryWindow(iRS_Window * pWnd)
{
	if (!pWnd) return;
	pWnd->UnInit();
	delete pWnd;
}

HRESULT RS_RendererDX11::SetRenderTarget(iRS_RenderTarget * pRT)
{
	if (!m_pContext) return E_FAIL;
	if (!pRT) {
		m_pContext->OMSetRenderTargets(0, nullptr,nullptr);
		return S_OK;
	}
	RS_RenderTargetDX11* pDX11RT = dynamic_cast<RS_RenderTargetDX11*>(pRT);
	if (!pDX11RT) return E_FAIL;
	
	m_pContext->OMSetRenderTargets( pDX11RT->GetRenderTargetViewSize(), pDX11RT->GetRenderTargetView(), pDX11RT->GetDepthStencilView());

	return S_OK;
}

void RS_RendererDX11::ClearRenderTarget(iRS_RenderTarget * pRT, const Color & color, float depth)
{
	if (!pRT || !m_pContext) return;
	RS_RenderTargetDX11* pDX11RT = dynamic_cast<RS_RenderTargetDX11*>(pRT);
	if (!pDX11RT) return;
	float col[4] = { color.r,color.g,color.b, color.a };
	ID3D11RenderTargetView** pRTVs = pDX11RT->GetRenderTargetView();
	unsigned nSize = pDX11RT->GetRenderTargetViewSize();
	for (unsigned i = 0; i < nSize; ++i) {
		if (pRTVs[i])
			m_pContext->ClearRenderTargetView(pRTVs[i], col);
	}
	ID3D11DepthStencilView* pDSV = pDX11RT->GetDepthStencilView();
	if (pDSV) {
		unsigned clearFlags = D3D11_CLEAR_DEPTH| D3D11_CLEAR_STENCIL;
		m_pContext->ClearDepthStencilView(pDSV, clearFlags,depth,0);
	}
}

RS_RendererDX11 * Cast2RendererDX11(iRS_Renderer * pRenderer)
{
	if (!pRenderer) return  nullptr;
	RS_RendererDX11* pRendererDX11 = dynamic_cast<RS_RendererDX11*>(pRenderer);
	return pRendererDX11;
}
