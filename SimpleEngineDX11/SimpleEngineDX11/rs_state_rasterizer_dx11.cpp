#include "rs_state_rasterizer_dx11.h"
#include "rs_renderer_dx11.h"

RS_RasterizerStateDX11::RS_RasterizerStateDX11()
{
	m_eCullType = eRS_CullBack;
	m_eFillModel = eRS_Solid;
	m_bMutilSample = true;
	m_bScissor = false;
	m_fDepthBais = 0;
	m_fSlopeDepthBais = 0;
	m_bDirty = true;
	m_pRasterizerState = nullptr;
}

void RS_RasterizerStateDX11::SetCullType(eRS_CullType cullType)
{
	if (m_eCullType == cullType) return;
	m_eCullType = cullType;
	m_bDirty = true;
}

void RS_RasterizerStateDX11::SetFillMode(eRS_FillMode fillMode)
{
	if (m_eFillModel == fillMode) return;
	m_eFillModel = fillMode;
	m_bDirty = true;
}

void RS_RasterizerStateDX11::SetMultiSample(bool enable)
{
	if (m_bMutilSample == enable) return;
	m_bMutilSample = enable;
	m_bDirty = true;
}

void RS_RasterizerStateDX11::SetScissor(bool enable)
{
	if (m_bScissor == enable) return;
	m_bScissor = enable;
	m_bDirty = true;
}

void RS_RasterizerStateDX11::SetDepthBais(float depthBais)
{
	if (m_fDepthBais == depthBais) return;
	m_fDepthBais = depthBais;
	m_bDirty = true;
}

void RS_RasterizerStateDX11::SetSlopeDepthBais(float slopeDepthBais)
{
	if (m_fSlopeDepthBais == slopeDepthBais) return;
	m_fSlopeDepthBais = slopeDepthBais;
	m_bDirty = true;
}

HRESULT RS_RasterizerStateDX11::DoState(iRS_Renderer * pRenderer)
{
	RS_RendererDX11* pRendererDX11 = Cast2RendererDX11(pRenderer);
	if (!pRendererDX11) return E_FAIL;
	ID3D11DeviceContext* pContext = pRendererDX11->GetContext();
	ID3D11Device* pDevice = pRendererDX11->GetDevice();
	if (!pContext || !pDevice) return E_FAIL;
	if (!m_pRasterizerState || m_bDirty) {
		if (m_pRasterizerState) {
			m_pRasterizerState->Release();
			m_pRasterizerState = nullptr;
		}
		m_bDirty = false;
		D3D11_RASTERIZER_DESC descRasterizer;
		descRasterizer.FillMode = cast2D3DFillMode(m_eFillModel);
		descRasterizer.CullMode = cast2D3DCullMode(m_eCullType);
		descRasterizer.FrontCounterClockwise = true;
		descRasterizer.DepthBias = (INT)m_fDepthBais;
		descRasterizer.DepthBiasClamp = 0;
		descRasterizer.SlopeScaledDepthBias = m_fSlopeDepthBais;
		descRasterizer.DepthClipEnable = TRUE;
		descRasterizer.ScissorEnable = (BOOL)m_bScissor;
		descRasterizer.MultisampleEnable = (BOOL)m_bMutilSample;
		descRasterizer.AntialiasedLineEnable = FALSE;
		if (FAILED(pDevice->CreateRasterizerState(&descRasterizer, &m_pRasterizerState))) {
			printf("creating depthState fails \n");
			return E_FAIL;
		}
	}
	pContext->RSSetState(m_pRasterizerState);
	return S_OK;
}

D3D11_FILL_MODE RS_RasterizerStateDX11::cast2D3DFillMode(eRS_FillMode fillMode)
{
	D3D11_FILL_MODE d3dFillMode;
	switch (fillMode)
	{
	case eRS_Solid:
		d3dFillMode = D3D11_FILL_SOLID;
		break;
	case eRS_WireFrame:
		d3dFillMode = D3D11_FILL_WIREFRAME;
		break;
	default:
		d3dFillMode = D3D11_FILL_SOLID;
		break;
	}
	return d3dFillMode;
}

D3D11_CULL_MODE RS_RasterizerStateDX11::cast2D3DCullMode(eRS_CullType cullType)
{
	D3D11_CULL_MODE d3dCullMode;
	switch (cullType)
	{
	case eRS_CullBack:
		d3dCullMode = D3D11_CULL_BACK;
		break;
	case eRS_CullFront:
		d3dCullMode = D3D11_CULL_FRONT;
		break;
	case eRS_CullNone:
		d3dCullMode = D3D11_CULL_NONE;
		break;
	default:
		d3dCullMode = D3D11_CULL_BACK;
		break;
	}
	return d3dCullMode;
}

