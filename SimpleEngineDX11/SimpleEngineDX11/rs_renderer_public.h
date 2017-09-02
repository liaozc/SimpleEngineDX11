#ifndef RS_RENDERER_PUBLIC_H
#define RS_RENDERER_PUBLIC_H

#include"platform.h"

#include "rs_buffer_public.h"
#include "rs_texture_public.h"
#include "rs_shader_public.h"
#include "rs_window_public.h"
#include "rs_rendertarget_public.h"
#include "color.h"
#include "data_type.h"

class iRS_Window;

class iRS_Renderer
{
public:
	virtual HRESULT		Init() = 0;
	virtual void		UnInit() = 0;
public:
	virtual iRS_Texture*	CreateTexture2D(int width, int height, eRS_ResourceFormat format,void* data) = 0;
	virtual iRS_Texture*	CreateTexture2DFromeFile(LPCSTR pFilePath) = 0;
	virtual iRS_Buffer*		CreateVertBuffer(eRS_BufferType bufferType,int size, void* data = nullptr) = 0;
	virtual iRS_Buffer*		CreateIndexBuffer(int size, void* data) = 0;
	virtual iRS_Shader**	CreateShaderFromFile(LPCSTR pFilePath,int& uSize) = 0;
	virtual iRS_Shader **	CreateShaderFromMemry(char * const pMemory, int & uSize) = 0;
	virtual iRS_Window*		CreateWindowFromHandle(HWND hwnd) = 0;
	virtual void			DestoryWindow(iRS_Window* pWnd) = 0;
	virtual HRESULT			SetRenderTarget(iRS_RenderTarget* pRT) = 0;
	virtual void			ClearRenderTarget(iRS_RenderTarget* pRT,const Color& color = COLOR_RED,float depth = 1.0f) = 0;
}; 

#endif