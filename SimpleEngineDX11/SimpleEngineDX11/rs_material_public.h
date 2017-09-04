#ifndef RS_MATERIAL_PUBLIC_H
#define RS_MATERIAL_PUBLIC_H

//todo: 目前的材质就是一堆状态设置，Shader组成
#include "rs_state_blend_public.h"
#include "rs_state_depth_public.h"
#include "rs_state_rasterizer_public.h"
#include "rs_shader_public.h"
#include "data_type.h"

class iRS_Renderer;

class iRS_Material
{
public:
	virtual iRS_BlendState* GetBlendState() const = 0;
	virtual iRS_DepthState* GetDepthState() const = 0;
	virtual iRS_RasterizerState* GetRasterizerState() const = 0;
	virtual void SetBlendState(iRS_BlendState* blendState) = 0;
	virtual void SetDepthState(iRS_DepthState* depthState) = 0;
	virtual void SetRasterizerState(iRS_RasterizerState* rasterizerState) = 0;
	virtual iRS_Shader* GetShader(eRS_ShaderType  shaderType) const = 0;
	virtual void SetShader(iRS_Shader** pShaders,int size) = 0;
	virtual HRESULT Apply(iRS_Renderer* pRenderer) = 0;
};


#endif
