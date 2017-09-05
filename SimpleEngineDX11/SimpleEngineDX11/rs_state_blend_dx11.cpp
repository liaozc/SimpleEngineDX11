#include "rs_state_blend_dx11.h"
#include "rs_renderer_dx11.h"

RS_BlendStateDX11::RS_BlendStateDX11()
{
	m_sBlendConfig.src = eRS_One;
	m_sBlendConfig.dst = eRS_Zero;
	m_pBlendState = nullptr;
	m_bDirty = true;
}

RS_BlendStateDX11::~RS_BlendStateDX11()
{
	if (m_pBlendState)
		m_pBlendState->Release();
	m_pBlendState = nullptr;
}

HRESULT RS_BlendStateDX11::DoState(iRS_Renderer * pRenderer)
{
	RS_RendererDX11* pRendererDX11 = Cast2RendererDX11(pRenderer);
	if (!pRendererDX11) return E_FAIL;
	ID3D11DeviceContext* pContext = pRendererDX11->GetContext();
	ID3D11Device* pDevice = pRendererDX11->GetDevice();
	if (!pContext || !pDevice) return E_FAIL;
	if (!m_pBlendState || m_bDirty) {
		if (m_pBlendState) {
			m_pBlendState->Release();
			m_pBlendState = nullptr;
		}
		m_bDirty = false;
		D3D11_BLEND_DESC descBlendState;
		descBlendState.AlphaToCoverageEnable = false;
		descBlendState.IndependentBlendEnable = false;
		descBlendState.RenderTarget->BlendEnable = true;
		descBlendState.RenderTarget->BlendOp = D3D11_BLEND_OP_ADD;
		descBlendState.RenderTarget->BlendOpAlpha = D3D11_BLEND_OP_ADD;
		descBlendState.RenderTarget->SrcBlend = cast2DX11BlendFormat(m_sBlendConfig.src);
		descBlendState.RenderTarget->DestBlend = cast2DX11BlendFormat(m_sBlendConfig.dst);
		descBlendState.RenderTarget->SrcBlendAlpha = cast2DX11BlendFormat(m_sBlendConfig.src);
		descBlendState.RenderTarget->DestBlendAlpha = cast2DX11BlendFormat(m_sBlendConfig.dst);
		descBlendState.RenderTarget->RenderTargetWriteMask = (UINT8)0;
		if (FAILED(pDevice->CreateBlendState(&descBlendState, &m_pBlendState))) {
			printf("creating blendstat fails \n");
			return E_FAIL;
		}
	}
	float blendcolor[4] = { 0,0,0,0 };
	pContext->OMSetBlendState(m_pBlendState, blendcolor, UINT(0));
	return S_OK;
}


void RS_BlendStateDX11::SetBlendConfig(const BlendCongfig& config)
{
	if (m_sBlendConfig == config) return;
	m_sBlendConfig = config;
	m_bDirty = true;
}

void RS_BlendStateDX11::SetBlendState(eRS_BlendOption src, eRS_BlendOption dst)
{
	if (src == m_sBlendConfig.src && dst == m_sBlendConfig.dst) return;
	m_sBlendConfig.src = src;
	m_sBlendConfig.dst = dst;
	m_bDirty = true;
}

D3D11_BLEND RS_BlendStateDX11::cast2DX11BlendFormat(eRS_BlendOption option)
{
	D3D11_BLEND d3dblend;
	switch (option)
	{
	case eRS_Zero:
		d3dblend = D3D11_BLEND_ZERO;
		break;
	case eRS_One:
		d3dblend = D3D11_BLEND_ONE;
		break;
	case eRS_Src_Color:
		d3dblend = D3D11_BLEND_SRC_COLOR;
		break;
	case eRS_One_Minus_Src_Color:
		d3dblend = D3D11_BLEND_INV_SRC_COLOR;
		break;
	case eRS_Dst_Color:
		d3dblend = D3D11_BLEND_DEST_COLOR;
		break;
	case eRS_One_Minus_Dst_Color:
		d3dblend = D3D11_BLEND_INV_DEST_COLOR;
		break;
	case eRS_Src_Alpha:
		d3dblend = D3D11_BLEND_SRC_ALPHA;
		break;
	case eRS_One_Minus_Src_Alpha:
		d3dblend = D3D11_BLEND_INV_SRC_ALPHA;
		break;
	case eRS_Dst_Alpha:
		d3dblend = D3D11_BLEND_DEST_ALPHA;
		break;
	case eRS_One_Minus_Dst_Alpha:
		d3dblend = D3D11_BLEND_INV_DEST_ALPHA;
		break;
	case eRS_Src_Alpha_Saturate:
		d3dblend = D3D11_BLEND_SRC_ALPHA_SAT;
		break;
	default:
		d3dblend = D3D11_BLEND_ZERO;
		break;
	}
	return d3dblend;
}
