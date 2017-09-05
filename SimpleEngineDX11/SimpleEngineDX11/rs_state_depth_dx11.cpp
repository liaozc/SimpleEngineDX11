#include "rs_state_depth_dx11.h"
#include "rs_renderer_dx11.h"

RS_DepthStateDX11::RS_DepthStateDX11()
{
	m_bDepthTest = true;
	m_bDepthWrite = true;
	m_bStencilTest = false;
	m_cWriteMask = 0;
	m_cReadMask = 0;
	m_eDepthFunc = eRS_Less;
	m_eStencilFunc = eRS_Equal;
	m_eDSOP_StencilPass = eRS_Keep;
	m_eDSOP_StencilFail = eRS_Keep;
	m_eDSOP_DepthFail = eRS_Keep;
	m_bDirty = true;
	m_pDepthState = nullptr;
}

RS_DepthStateDX11::~RS_DepthStateDX11()
{
	if (m_pDepthState)
		m_pDepthState->Release();
	m_pDepthState = nullptr;
}


void RS_DepthStateDX11::SetDepthTest(bool enable)
{
	if (m_bDepthTest == enable) return;
	m_bDepthTest = enable;
	m_bDirty = true;
}

void RS_DepthStateDX11::SetStencilTest(bool enable)
{
	if (m_bStencilTest == enable) return;
	m_bStencilTest = enable;
	m_bDirty = true;
}

void RS_DepthStateDX11::SetStencilWriteMask(byte mask)
{
	if (m_cWriteMask == mask) return;
	m_cWriteMask = mask;
	if (m_bStencilTest) m_bDirty = true;
}

void RS_DepthStateDX11::SetStencilReadMask(byte mask)
{
	if (m_cReadMask == mask) return;
	m_cReadMask = mask;
	if (m_bStencilTest) m_bDirty = true;
}


void RS_DepthStateDX11::SetDepthWriteEnable(bool enable)
{
	if (m_bDepthWrite == enable) return;
	m_bDepthWrite = enable;
	if (m_bDepthTest) m_bDirty = true;
}

void RS_DepthStateDX11::SetDepthFunc(eRS_ComparisonFunction depthfunc)
{
	if (m_eDepthFunc == depthfunc) return;
	m_eDepthFunc = depthfunc;
	if(m_bDepthTest)  m_bDirty = true;
}

void RS_DepthStateDX11::SetStencilFunc(eRS_ComparisonFunction stencilfunc)
{
	if (m_eStencilFunc == stencilfunc) return;
	m_eStencilFunc = stencilfunc;
	if (m_bStencilTest)  m_bDirty = true;
}

void RS_DepthStateDX11::SetStencilFail(eRS_DepthStencilOperation operation)
{
	if (m_eDSOP_StencilFail == operation) return;
	m_eDSOP_StencilFail = operation;
	if (m_bStencilTest)  m_bDirty = true;
}

void RS_DepthStateDX11::SetStencilPass(eRS_DepthStencilOperation operation)
{
	if (m_eDSOP_StencilPass == operation) return;
	m_eDSOP_StencilPass = operation;
	if (m_bStencilTest)  m_bDirty = true;
}

void RS_DepthStateDX11::SetDepthlFail(eRS_DepthStencilOperation operation)
{
	if (m_eDSOP_DepthFail == operation) return;
	m_eDSOP_DepthFail = operation;
	if (m_bDepthTest)  m_bDirty = true;
}

HRESULT RS_DepthStateDX11::DoState(iRS_Renderer * pRenderer)
{
	RS_RendererDX11* pRendererDX11 = Cast2RendererDX11(pRenderer);
	if (!pRendererDX11) return E_FAIL;
	ID3D11DeviceContext* pContext = pRendererDX11->GetContext();
	ID3D11Device* pDevice = pRendererDX11->GetDevice();
	if (!pContext || !pDevice) return E_FAIL;
	if (!m_pDepthState || m_bDirty) {
		if (m_pDepthState) {
			m_pDepthState->Release();
			m_pDepthState = nullptr;
		}
		m_bDirty = false;
		D3D11_DEPTH_STENCIL_DESC descDepthStencilState;
		descDepthStencilState.DepthEnable = m_bDepthTest;
		descDepthStencilState.DepthWriteMask = m_bDepthWrite ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
		descDepthStencilState.DepthFunc = cast2D3DComparisonFunc(m_eDepthFunc);
		descDepthStencilState.StencilEnable = m_bStencilTest;
		descDepthStencilState.StencilWriteMask = m_cWriteMask;
		descDepthStencilState.StencilReadMask = m_cReadMask;
		descDepthStencilState.FrontFace.StencilDepthFailOp = cast2D3DStencilOP(m_eDSOP_DepthFail);
		descDepthStencilState.FrontFace.StencilFailOp = cast2D3DStencilOP(m_eDSOP_StencilFail);
		descDepthStencilState.FrontFace.StencilPassOp = cast2D3DStencilOP(m_eDSOP_StencilFail);
		descDepthStencilState.BackFace.StencilDepthFailOp = cast2D3DStencilOP(m_eDSOP_DepthFail);
		descDepthStencilState.BackFace.StencilFailOp = cast2D3DStencilOP(m_eDSOP_StencilFail);
		descDepthStencilState.BackFace.StencilPassOp = cast2D3DStencilOP(m_eDSOP_StencilFail);
		if (FAILED(pDevice->CreateDepthStencilState(&descDepthStencilState, &m_pDepthState))) {
			printf("creating depthState fails \n");
			return E_FAIL;
		}
	}
	pContext->OMSetDepthStencilState(m_pDepthState, 0);
	return S_OK;
}

D3D11_COMPARISON_FUNC RS_DepthStateDX11::cast2D3DComparisonFunc(eRS_ComparisonFunction eCompareFun)
{
	D3D11_COMPARISON_FUNC d3dcompareFun;
	switch (eCompareFun)
	{
	case eRS_Never:
		d3dcompareFun = D3D11_COMPARISON_NEVER;
		break;
	case eRS_Less:
		d3dcompareFun = D3D11_COMPARISON_LESS;
		break;
	case eRS_Equal:
		d3dcompareFun = D3D11_COMPARISON_EQUAL;
		break;
	case eRS_LEqual:
		d3dcompareFun = D3D11_COMPARISON_LESS_EQUAL;
		break;
	case eRS_Greater:
		d3dcompareFun = D3D11_COMPARISON_GREATER;
		break;
	case eRS_NotEqual:
		d3dcompareFun = D3D11_COMPARISON_NOT_EQUAL;
		break;
	case eRS_GEqual:
		d3dcompareFun = D3D11_COMPARISON_GREATER_EQUAL;
		break;
	case eRS_Always:
		d3dcompareFun = D3D11_COMPARISON_ALWAYS;
		break;
	default:
		d3dcompareFun = D3D11_COMPARISON_NEVER;
		break;
	}
	return d3dcompareFun;
	
}

D3D11_STENCIL_OP RS_DepthStateDX11::cast2D3DStencilOP(eRS_DepthStencilOperation eOperation)
{
	D3D11_STENCIL_OP d3dStencilOP;
	switch (eOperation)
	{
	case eRS_Keep:
		d3dStencilOP = D3D11_STENCIL_OP_KEEP;
		break;
	case eRS_Set_Zero:
		d3dStencilOP = D3D11_STENCIL_OP_ZERO;
		break;
	case eRS_Replace:
		d3dStencilOP = D3D11_STENCIL_OP_REPLACE;
		break;
	case eRS_Invert:
		d3dStencilOP = D3D11_STENCIL_OP_INVERT;
		break;
	case eRS_Incr:
		d3dStencilOP = D3D11_STENCIL_OP_INCR;
		break;
	case eRS_Decr:
		d3dStencilOP = D3D11_STENCIL_OP_DECR;
		break;
	case eRS_Incr_Sat:
		d3dStencilOP = D3D11_STENCIL_OP_INCR_SAT;
		break;
	case eRS_Decr_Sat:
		d3dStencilOP = D3D11_STENCIL_OP_DECR_SAT;
		break;
	default:
		d3dStencilOP = D3D11_STENCIL_OP_KEEP;
		break;
	}
	return d3dStencilOP;
}
