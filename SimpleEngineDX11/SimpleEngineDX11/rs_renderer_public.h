#ifndef RS_RENDERER_PUBLIC_H
#define RS_RENDERER_PUBLIC_H

#include"platform.h"

#include "rs_buffer_public.h"
#include "rs_texture_public.h"
#include "rs_shader_public.h"
#include "rs_window_public.h"
#include "rs_rt_public.h"
#include "color.h"

class iRS_Window;

enum eVertDataFormat
{
	eVDF_Position,
	eVDF_Normal,
	eVDF_Color,
	eVDF_Texturecoord,
	eVDF_Count,
};


enum eTextureDataFormat 
{
	eTDF_R8B8G8A8,
	eTDF_R8B8G8,
	eTDF_R8,
	eTDF_Count,
};

class iRS_Renderer
{
public:
	virtual HRESULT		Init() = 0;
	virtual void		UnInit() = 0;
public:
	virtual iRS_Texture*	CreateTexture2D(int width, int height, eTextureDataFormat format,void* data) = 0;
	virtual iRS_Texture*	CreateTexture2DFromeFile(LPCSTR pFilePath) = 0;
	virtual iRS_Buffer*		CreateVertBuffer(int size, void* data, eVertDataFormat* pDataForm, int formSize) = 0;
	virtual iRS_Buffer*		CreateIndexBuffer(int size, void* data) = 0;
	virtual iRS_Shader*		CreateVShaderFromFile(LPCSTR pFilePath) = 0;
	virtual iRS_Shader*		CreateVShaderFromMemory(byte* pMemory) = 0;
	virtual iRS_Window*		CreateWindowFromHandle(HWND hwnd) = 0;
	virtual void			DestoryWindow(iRS_Window* pWnd) = 0;
	virtual HRESULT			SetRenderTarget(iRS_RenderTarget* pRT) = 0;
	virtual void			ClearRenderTarget(iRS_RenderTarget* pRT,const Color& color = COLOR_RED,float depth = 1.0f) = 0;
}; 

#endif