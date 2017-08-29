#include "render_target_win32.h"
#include "engine_public.h"
#include <d3d11.h>


extern "C" 
iRenderTarget* CreateRTWindow(iEngine* pEngine, wndHandle hwnd)
{
	RTWindow* pRTWnd = new RTWindow();
	pRTWnd->Init(pEngine);
	pRTWnd->BindWndHandle(hwnd);
	return pRTWnd;
}


void RTWindow::Init(iEngine * pEngine)
{
	m_pEngine = pEngine;
}

void RTWindow::OnAttached()
{
}

void RTWindow::OnDetached()
{
}

void RTWindow::BindWndHandle(wndHandle hwnd)
{
	if (m_hwnd != wndHandle(0)) return;
	m_hwnd = hwnd;
	if (!m_pEngine) return;
	//create swapchain here
	ID3D11Device* pD3DDevice = m_pEngine->GetDevice();
	if (!pD3DDevice) return;
	IDXGIFactory1 *dxgiFactory;
	if (FAILED(CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void **)&dxgiFactory))) return;
	IDXGIAdapter1 *dxgiAdapter;
	if (dxgiFactory->EnumAdapters1(0, &dxgiAdapter) == DXGI_ERROR_NOT_FOUND) return;
	IDXGIOutput *dxgiOutput;
	if (dxgiAdapter->EnumOutputs(0, &dxgiOutput) == DXGI_ERROR_NOT_FOUND) return;
	DXGI_OUTPUT_DESC oDesc;
	dxgiOutput->GetDesc(&oDesc);
	// Find a suitable fullscreen format
	int targetHz = 85;
	DXGI_RATIONAL fullScreenRefresh;
	int fsRefresh = 60;
	fullScreenRefresh.Numerator = fsRefresh;
	fullScreenRefresh.Denominator = 1;
	
	RECT rect;
	GetClientRect(m_hwnd, &rect);

	int msaaSamples = 4;
	DXGI_FORMAT backBufferFormat = DXGI_FORMAT_R32G32B32_UINT;
	//check msaa ability
	while (msaaSamples > 0)	{
		UINT nQuality;
		if (SUCCEEDED(pD3DDevice->CheckMultisampleQualityLevels(backBufferFormat, msaaSamples, &nQuality)) && nQuality > 0)	
			break;
		else
			msaaSamples -= 2;
	}
	DXGI_SWAP_CHAIN_DESC sd;
	memset(&sd, 0, sizeof(sd));
	sd.BufferDesc.Width = rect.right;
	sd.BufferDesc.Height = rect.bottom;
	sd.BufferDesc.Format = backBufferFormat;
	sd.BufferDesc.RefreshRate = fullScreenRefresh;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 2;
	sd.OutputWindow = m_hwnd;
	sd.Windowed = FALSE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	sd.SampleDesc.Count = msaaSamples;
	sd.SampleDesc.Quality = 0;
	if (FAILED(dxgiFactory->CreateSwapChain(pD3DDevice, &sd, &m_pSwapChain))) return;
	dxgiFactory->MakeWindowAssociation(hwnd, DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER);
	dxgiOutput->Release();
	dxgiAdapter->Release();
	dxgiFactory->Release();
}
