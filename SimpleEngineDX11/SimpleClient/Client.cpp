
#include "engine_public.h"
#include "rs_renderer_public.h"
#include "geo_mesh.h"
#include "mth_math.h"

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
	ShowWindow(hwnd,TRUE);

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

	HWND hwnd = CreateOuputWindow(640, 480);

	iRS_Renderer* pRenderer = g_pEngine->GetRenderer();
	g_pWnd = pRenderer->CreateWindowFromHandle(hwnd);
	iRS_RenderTarget* pMainRT = g_pWnd->GetRenderTarget();
	pRenderer->SetRenderTarget(pMainRT);

	LPCSTR tsShader = "E:\\SimpleEngineDX11\\SimpleEngineDX11\\x64\\Debug\\ShaderTest.shd";
	int uSize = 0;
	iRS_Shader** pShaders = pRenderer->CreateShaderFromFile(tsShader, uSize);
	Matrix m;
	m.m00 = m.m11 = m.m22 = 0.5f;
	m.m33 = 1.0f;
	pShaders[0]->SetConstant4x4f("worldViewProj",m);
	pShaders[1]->SetConstant3f("testColr", Vector3(0, 0, 1));
	iRS_Shader* pShader0 = pShaders[0];
	Vector3 pMeshVertex[] = { Vector3(0,0,0),Vector3(0,1,0),Vector3(1,0,0) };
	UINT16 pMeshIndice[] = { 0,1,2};
	eRS_VertDataFormat pMeshFormat[] = {eRS_VertDataFormat_Position};
	iGEO_Manager* pGeoMgr = g_pEngine->GetGeometryManager();
	Mesh* pMesh = pGeoMgr->CreateMesh(pMeshVertex, 3, sizeof(Vector3), pMeshIndice, 3, sizeof(UINT16), pMeshFormat, 1);
	iRS_MeshRenderer* pMeshRenderer = pRenderer->CreateMeshRenderer();
	iRS_Material* pMat = pRenderer->CreateMaterial();
	pMat->SetShader(pShaders, uSize);
	pMeshRenderer->SetMaterial(pMat);
	pMeshRenderer->SetMesh(pMesh);
	
	for (int i = 0; i < uSize; ++i) SAFE_RELEASE(pShaders[i]);
	SAFE_DELETE_ARRAY(pShaders);
	SAFE_RELEASE(pMat); //所有get回来的东西都不用release，但是所有Create回来的都需要释放


	float scale = 1.0;
	bool bInOrder = true;
	while (bIsRunning){
		MSG msg;
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		pRenderer->ClearRenderTarget(g_pWnd->GetRenderTarget(),Color(0.5f,0.5f,0.5f,0.5f));

		if (bInOrder) {
			scale -= 0.01f;
			if (scale <= 0.5f)
				bInOrder = false;
		}
		else {
			scale += 0.01f;
			if (scale >= 1.0f)
				bInOrder = true;
		}
		m.m00 = m.m11 = m.m22 = scale;
		pShader0->SetConstant4x4f("worldViewProj", m);
		
		pMeshRenderer->DoRender();

		/*
		[
			iMesh pMesh = new Mesh();
			iMesheRenderer pMeshRenderer = new MeshRenderer();
			iMaterial pMaterial = new Material();
			pMeshRenderer->SetMesh(pMesh);
			pMeshrRenderer->setMaterial(pMaterial);
			pMaterial -> setBlendState( new BlendState());
			pMaterial -> setRasterizerState( new RasterizerState() );
			pMaterial -> setDepthState( new DepthState() );
			iShader pVS = new Shader(VERT_SHADER)
			iShader pFS = new Shader(FRAG_SHADER)
			pMaterial -> setVShader( pVS);
			pMaterial -> setPShader( pFS);
			iSceneObject pSceneObj = new SceneObject();
			pSceneObj->SetMeshRenderer(pMeshRenderer);
			pScene->AddObj(pSceneObj);
			pScene->DoRender(pRenderer);
			[
				for(obj in objs)
					obj->GetMeshRenderer()->DoRender(pRenderer);
					[
						T = GetTransform();
						pMaterial->GetVShader()->SetShaderConstant(T)
						pMaterial->Apply(pRenderer);
						pContext->setVB(VB)
						pContext->setIB(IB)
						pContext->Draw();
					]
			]
		]
		*/

		g_pWnd->Present();
		Sleep(30);
	}
	printf("quitting...\n");
	pMeshRenderer->Release();
	g_pWnd->Release();
	pfnDestruct();
	return 1;
}