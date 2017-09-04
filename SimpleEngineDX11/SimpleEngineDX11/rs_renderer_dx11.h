#ifndef RS_RENDERER_DX11_H
#define RS_RENDERER_DX11_H

#include <d3d11.h>
#include "rs_renderer_public.h"
class RS_ShaderManagerDX11;
class iRS_MeshRenderer;

class RS_RendererDX11 : public iRS_Renderer
{
public:
	virtual HRESULT Init();
	virtual void	UnInit();

public:
	virtual iRS_Texture*	CreateTexture2D(int width, int height, eRS_ResourceFormat format, void* data);
	virtual iRS_Texture*	CreateTexture2DFromeFile(LPCSTR pFilePath);
	virtual iRS_Buffer*		CreateVertBuffer(eRS_BufferType bufferType,int size, void* data = nullptr);
	virtual iRS_Buffer*		CreateIndexBuffer(int size, void* data);
	virtual iRS_Shader**	CreateShaderFromFile(LPCSTR pFilePath, int& uSize);
	virtual iRS_Shader **	CreateShaderFromMemry(char * const pMemory, int & uSize);
	virtual iRS_Window*		CreateWindowFromHandle(HWND hwnd);
	virtual void			DestoryWindow(iRS_Window* pWnd);
	virtual HRESULT			SetRenderTarget(iRS_RenderTarget* pRT);
	virtual void			ClearRenderTarget(iRS_RenderTarget* pRT, const Color& color = COLOR_BLUE, float depth = 1.0f);
	virtual iRS_MeshRenderer* CreateMeshRenderer();
	virtual iRS_Material* CreateMaterial();
public:
	ID3D11Device*			GetDevice() const { return m_pDevice; }
	ID3D11DeviceContext*	GetContext() const { return m_pContext; }

protected:
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pContext;
	RS_ShaderManagerDX11* m_pShaderMgr;
};

RS_RendererDX11* Cast2RendererDX11(iRS_Renderer* pRenderer);

#endif
