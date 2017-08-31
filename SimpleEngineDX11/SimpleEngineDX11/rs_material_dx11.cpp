#include "rs_material_dx11.h"

RS_MaterialDX11::RS_MaterialDX11()
{
	m_pBlendState = nullptr;
	m_pDepthState = nullptr;
	m_pRasterizerState = nullptr;
	m_pVShader = nullptr;
	m_pFShader = nullptr;
	m_pGShader = nullptr;
	m_pCShader = nullptr;
}	

iRS_Shader * RS_MaterialDX11::GetShader(eRS_ShaderType shaderType) const
{
	iRS_Shader* pRet = nullptr;
	switch (shaderType)
	{
	case eRS_VertShader:
		pRet = m_pVShader;
		break;
	case eRS_FragmentShader:
		pRet = m_pFShader;
		break;
	case eRS_GeometryShader:
		pRet = m_pGShader;
		break;
	case eRS_ComputeShader:
		pRet = m_pCShader;
		break;
	}
	return pRet;
}

HRESULT RS_MaterialDX11::Apply(iRS_Renderer * pRenderer)
{
	HRESULT hRet = E_FAIL;
	do {
		if (m_pDepthState)
			if (FAILED(m_pDepthState->DoState(pRenderer))) break;
		if (m_pRasterizerState)
			if (FAILED(m_pRasterizerState->DoState(pRenderer))) break;
		if (m_pBlendState)
			if (FAILED(m_pBlendState->DoState(pRenderer))) break;

	} while (0);
	return S_OK;
}


