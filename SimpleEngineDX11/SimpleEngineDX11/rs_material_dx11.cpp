#include "rs_material_dx11.h"
#include "rs_state_rasterizer_dx11.h"

RS_MaterialDX11::RS_MaterialDX11()
{
	m_pBlendState = nullptr;
	m_pDepthState = nullptr;
	m_pRasterizerState = nullptr;
	m_pVShader = nullptr;
	m_pFShader = nullptr;
	m_pGShader = nullptr;
	m_pCShader = nullptr;

	m_pRasterizerState = new RS_RasterizerStateDX11();
	m_pRasterizerState->SetCullType(eRS_CullNone);
}	

RS_MaterialDX11::~RS_MaterialDX11()
{
	unInit();
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


void RS_MaterialDX11::SetBlendState(iRS_BlendState* blendState)
{
	SAFE_RELEASE(m_pBlendState);
	m_pBlendState = blendState;
	SAFE_ADDREF(m_pBlendState);
}

void RS_MaterialDX11::SetDepthState(iRS_DepthState* depthState)
{
	SAFE_RELEASE(m_pDepthState);
	m_pDepthState = depthState;
	SAFE_ADDREF(m_pDepthState);
}

void RS_MaterialDX11::SetRasterizerState(iRS_RasterizerState* rasterizerState)
{
	SAFE_RELEASE(m_pRasterizerState);
	m_pRasterizerState = rasterizerState;
	SAFE_ADDREF(m_pRasterizerState);
}

void RS_MaterialDX11::SetShader(iRS_Shader ** pShaders, int size)
{
	for (int i = 0; i < size; ++i) {
		setShader(pShaders[i]);
	}
}

void RS_MaterialDX11::setShader(iRS_Shader * pShader)
{
	if (pShader->GetType() == eRS_VertShader) {
		SAFE_RELEASE(m_pVShader);
		m_pVShader = pShader;
		m_pVShader->AddRef();
	}

	if (pShader->GetType() == eRS_GeometryShader) {
		SAFE_RELEASE(m_pGShader)
		m_pGShader = pShader;
		m_pVShader->AddRef();
	}

	if (pShader->GetType() == eRS_FragmentShader) {
		SAFE_RELEASE(m_pFShader)
		m_pFShader = pShader;
		m_pFShader->AddRef();
	}

	if (pShader->GetType() == eRS_ComputeShader) {
		SAFE_RELEASE(m_pCShader)
		m_pCShader = pShader;
		m_pCShader->AddRef();
	}
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
	
	if (m_pVShader) m_pVShader->DoShade();
	if (m_pGShader) m_pGShader->DoShade();
	if (m_pFShader) m_pFShader->DoShade();
	if (m_pCShader) m_pCShader->DoShade();


	return S_OK;
}

void RS_MaterialDX11::unInit()
{
	SAFE_RELEASE(m_pVShader);
	SAFE_RELEASE(m_pGShader);
	SAFE_RELEASE(m_pFShader);
	SAFE_RELEASE(m_pCShader);
	SAFE_RELEASE(m_pDepthState);
	SAFE_RELEASE(m_pRasterizerState);
	SAFE_RELEASE(m_pBlendState);
}
