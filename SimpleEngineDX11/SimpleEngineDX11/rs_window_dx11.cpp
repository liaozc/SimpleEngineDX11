#include "rs_window_dx11.h"
#include "rs_renderer_dx11.h"
#include "rs_rendertarget_dx11.h"

HRESULT RS_WindowDX11::Init(HWND hwnd, iRS_Renderer* pRenderer)
{
	m_pRT = nullptr;
	m_pSwapChain = nullptr;
	m_hwnd = 0;
	m_pDepthStencil = nullptr;
	m_nWidth = 0;
	m_nHeight = 0;
	m_backBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	m_pRenderer = pRenderer;

	if (hwnd == 0 || !m_pRenderer || m_hwnd != 0) return E_FAIL;
	RS_RendererDX11* pDX11Renderer = dynamic_cast<RS_RendererDX11*>(m_pRenderer);
	if (!pDX11Renderer || !pDX11Renderer->GetDevice()) return E_FAIL;
	m_hwnd = hwnd;
	ID3D11Device* pD3DDevice = pDX11Renderer->GetDevice();
	IDXGIFactory1 *dxgiFactory;
	if (FAILED(CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void **)&dxgiFactory))) return E_FAIL;
	IDXGIAdapter1 *dxgiAdapter;
	if (dxgiFactory->EnumAdapters1(0, &dxgiAdapter) == DXGI_ERROR_NOT_FOUND) return E_FAIL;
	IDXGIOutput *dxgiOutput;
	if (dxgiAdapter->EnumOutputs(0, &dxgiOutput) == DXGI_ERROR_NOT_FOUND) return E_FAIL;
	DXGI_OUTPUT_DESC oDesc;
	dxgiOutput->GetDesc(&oDesc);
	DXGI_RATIONAL fullScreenRefresh;
	int fsRefresh = 60;
	fullScreenRefresh.Numerator = fsRefresh;
	fullScreenRefresh.Denominator = 1;
	RECT rect;
	GetClientRect(m_hwnd, &rect);
	m_nWidth = rect.right - rect.left;
	m_nHeight = rect.bottom - rect.top;

	int msaaSamples = 4;
	while (msaaSamples > 0) {//check msaa ability
		UINT nQuality;
		if (SUCCEEDED(pD3DDevice->CheckMultisampleQualityLevels(m_backBufferFormat, msaaSamples, &nQuality)) && nQuality > 0)
			break;
		else
			msaaSamples -= 2;
	}
	m_nMSAA = msaaSamples > 1 ? msaaSamples : 1;
	DXGI_SWAP_CHAIN_DESC sd;
	memset(&sd, 0, sizeof(sd));
	sd.BufferDesc.Width = m_nWidth;
	sd.BufferDesc.Height = m_nHeight;
	sd.BufferDesc.Format = m_backBufferFormat;
	sd.BufferDesc.RefreshRate = fullScreenRefresh;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 2;
	sd.OutputWindow = m_hwnd;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	sd.SampleDesc.Count = m_nMSAA;
	sd.SampleDesc.Quality = 0;
	if (FAILED(dxgiFactory->CreateSwapChain(pD3DDevice, &sd, &m_pSwapChain))) return E_FAIL;
	dxgiFactory->MakeWindowAssociation(hwnd, DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER);
	dxgiOutput->Release();
	dxgiAdapter->Release();
	dxgiFactory->Release();

	
	return createRT();
}

RS_WindowDX11::~RS_WindowDX11()
{
	if (m_pSwapChain) {
		m_pSwapChain->Release();
		m_pSwapChain = nullptr;
	}
	m_hwnd = 0;
	if (m_pDepthStencil) {
		m_pDepthStencil->Release();
		m_pDepthStencil = nullptr;
	}
	if (m_pRT) {
		m_pRT->Release();
		m_pRT = nullptr;
	}
}

iRS_RenderTarget* RS_WindowDX11::GetRenderTarget() const
{
	return m_pRT;
}

void RS_WindowDX11::OnSize(HWND hwnd, unsigned w, unsigned h)
{
	if (m_hwnd != hwnd || (w == m_nWidth && h == m_nHeight)) return;
	m_nHeight = h;
	m_nWidth = w;
	SAFE_RELEASE(m_pRT);
	if (m_pDepthStencil) {
		m_pDepthStencil->Release();
		m_pDepthStencil = nullptr;
	}
	if (m_pSwapChain)
		m_pSwapChain->ResizeBuffers(2, m_nWidth, m_nHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
	createRT();
}

void RS_WindowDX11::Present()
{
	if (m_pSwapChain)
		m_pSwapChain->Present(0, 0);
}

HRESULT RS_WindowDX11::createRT()
{
	if (!m_pRenderer) return E_FAIL;
	RS_RendererDX11* pDX11Renderer = dynamic_cast<RS_RendererDX11*>(m_pRenderer);
	if (!pDX11Renderer) return E_FAIL;
	ID3D11Device* pD3DDevice = pDX11Renderer->GetDevice();
	//create RenderTargetView
	ID3D11Texture2D* backBuffer = nullptr;
	if (FAILED(m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer))) {
		printf("can't get swap_chain's backBuffer");
		return E_FAIL;
	}
	D3D11_RENDER_TARGET_VIEW_DESC descRT;
	descRT.Format = m_backBufferFormat;
	descRT.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
	descRT.Texture2D.MipSlice = 0;
	ID3D11RenderTargetView* pRTV = nullptr;
	if (FAILED(pD3DDevice->CreateRenderTargetView(backBuffer, &descRT, &pRTV))) {
		printf("can't create rtv\n");
		return E_FAIL;
	}
	backBuffer->Release();
	//create depthstencil and depthstencil view
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = m_nWidth;
	descDepth.Height = m_nHeight;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = m_nMSAA;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	if (FAILED(pD3DDevice->CreateTexture2D(&descDepth, NULL, &m_pDepthStencil))) {
		printf("can't create ds\n");
		return E_FAIL;
	}
	ID3D11DepthStencilView* pDSV = nullptr;
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = m_nMSAA > 1 ? D3D11_DSV_DIMENSION_TEXTURE2DMS : D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	descDSV.Flags = 0;
	if (FAILED(pD3DDevice->CreateDepthStencilView(m_pDepthStencil, &descDSV, &pDSV))) {
		printf("can't create dsv\n");
		return E_FAIL;
	}
	ID3D11RenderTargetView** pRTVAry = new ID3D11RenderTargetView*[1];
	pRTVAry[0] = pRTV;
	m_pRT = new RS_RenderTargetDX11(pRTVAry, 1, pDSV, m_nWidth,m_nHeight);
	pRTV->Release();
	pDSV->Release();
	return S_OK;
}
