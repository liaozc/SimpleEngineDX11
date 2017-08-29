
#include "engine_public.h"
#include "rs_renderer_public.h"

bool bIsRunning = true;
iEngine* g_pEngine = nullptr;
iRS_Window* g_pWnd = nullptr;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_PAINT:
		PAINTSTRUCT paint;
		BeginPaint(hWnd, &paint);
		EndPaint(hWnd, &paint);
		break;
	case WM_MOUSEMOVE:
		break;
	case WM_KEYDOWN:
		break;
	case WM_KEYUP:
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_MBUTTONDOWN:
		break;
	case WM_MBUTTONUP:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_RBUTTONUP:
		break;
	case WM_MOUSEWHEEL:
		break;
	case WM_SIZE:
		if (g_pEngine)
			g_pEngine->GetRenderer()->SetRenderTarget(nullptr);
		if (g_pWnd) 
			g_pWnd->OnSize(hWnd, LOWORD(lParam), HIWORD(lParam)); 
		if(g_pEngine && g_pWnd)
			g_pEngine->GetRenderer()->SetRenderTarget(g_pWnd->GetRenderTarget());
		break;
	case WM_WINDOWPOSCHANGED:
		if ((((LPWINDOWPOS)lParam)->flags & SWP_NOSIZE) == 0) {
			RECT rect;
			GetClientRect(hWnd, &rect);
			int w = rect.right - rect.left;
			int h = rect.bottom - rect.top;
			if (w > 0 && h > 0) {
				if (g_pEngine)
					g_pEngine->GetRenderer()->SetRenderTarget(nullptr);
				if (g_pWnd)
					g_pWnd->OnSize(hWnd, w, h);
				if (g_pEngine && g_pWnd)
					g_pEngine->GetRenderer()->SetRenderTarget(g_pWnd->GetRenderTarget());
			}
		}
		break;
	case WM_SYSKEYDOWN:
		break;
	case WM_SYSKEYUP:
		break;
	case WM_CREATE:
		ShowWindow(hWnd, SW_SHOW);
		break;
	case WM_CLOSE:
	case WM_QUIT:
		bIsRunning = false;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


HWND CreateOuputWindow(int width, int height)
{
	WNDCLASS wc;
	wc.style = CS_DBLCLKS;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = 0;
	wc.hIcon = LoadIcon(0, MAKEINTATOM(0));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "client";

	WORD bResult = RegisterClassA(&wc);
	
	HWND hwnd = CreateWindowExA(0, "client","client",WS_VISIBLE | WS_OVERLAPPEDWINDOW,0,0, width, height,NULL,NULL,NULL,NULL);
	
	UpdateWindow(hwnd);

	return hwnd;
}

int main()
{
	HMODULE hmdl = ::LoadLibraryA("SimpleEngineDX11.dll");
	if (hmdl == HMODULE(0)) {
		printf("load engine error\n");
		return 0;
	}
	pfnCreateEngineFunc pfnCreate = (pfnCreateEngineFunc)::GetProcAddress(hmdl, "CreateEngine");
	pfnDestructEngineFunc pfnDestruct = (pfnDestructEngineFunc)::GetProcAddress(hmdl, "DestructEngine");

	t_EngineConfigOptMap tMap;
	tMap[eECO_RendererType] = "dx11";
	g_pEngine = pfnCreate(tMap);
	if(!g_pEngine) {
		printf("load engine error\n");
		return 0; 
	}

	HWND hwnd = CreateOuputWindow(600, 480);

	iRS_Renderer* pRenderer = g_pEngine->GetRenderer();
	g_pWnd = pRenderer->CreateWindowFromHandle(hwnd);
	iRS_RenderTarget* pMainRT = g_pWnd->GetRenderTarget();
	pRenderer->SetRenderTarget(pMainRT);
	while (bIsRunning){
		MSG msg;
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		pRenderer->ClearRenderTarget(g_pWnd->GetRenderTarget());
		g_pWnd->Present();
		Sleep(5);
	}
	printf("quitting...\n");
	pRenderer->DestoryWindow(g_pWnd);
	pfnDestruct();
	return 1;
}