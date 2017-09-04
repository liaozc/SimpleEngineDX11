#ifndef RS_MATERIAL_DX11_H
#define RS_MATERIAL_DX11_H

#include "rs_renderer_public.h"
#include "rs_material_public.h"

class RS_MaterialDX11 : public iRS_Material
{
public:
	RS_MaterialDX11();
	virtual iRS_BlendState* GetBlendState() const { return m_pBlendState; }
	virtual iRS_DepthState* GetDepthState() const { return m_pDepthState; }
	virtual iRS_RasterizerState* GetRasterizerState() const { return m_pRasterizerState; }
	virtual void SetBlendState(iRS_BlendState* blendState) { m_pBlendState = blendState; }
	virtual void SetDepthState(iRS_DepthState* depthState) { m_pDepthState = depthState; }
	virtual void SetRasterizerState(iRS_RasterizerState* rasterizerState) { m_pRasterizerState = rasterizerState; }
	virtual iRS_Shader* GetShader(eRS_ShaderType  shaderType) const ;
	virtual void SetShader(iRS_Shader** pShaders, int size);
	virtual HRESULT Apply(iRS_Renderer* pRenderer);
protected:
	void SetShader(iRS_Shader * pShader);
protected:
	iRS_BlendState* m_pBlendState;
	iRS_DepthState* m_pDepthState;
	iRS_RasterizerState* m_pRasterizerState;
	iRS_Shader* m_pVShader;
	iRS_Shader* m_pFShader;
	iRS_Shader* m_pGShader;
	iRS_Shader* m_pCShader;
};

#endif
