#include "rs_state_sampler_dx11.h"
#include "rs_renderer_dx11.h"

RS_SampleState::RS_SampleState()
{
	m_eFilter = eRS_Bilinear;
	m_eU = eRS_Wrap;
	m_eV = eRS_Wrap;
	m_eW = eRS_Wrap;
	m_fMipLodBais = 0;
	m_fMaxAniso = 0;
	m_eCompareFun = eRS_LEqual;
	m_bDirty = true;
	m_pSamplerState = nullptr;
}

RS_SampleState::~RS_SampleState()
{
	if (m_pSamplerState)
		m_pSamplerState->Release();
	m_pSamplerState = nullptr;
}

void RS_SampleState::SetFilter(eRS_Filter filter)
{
	if (m_eFilter == filter) return;
	m_eFilter = filter;
	m_bDirty = true;
}

void RS_SampleState::SetAddressMode(eRS_AddressMode u, eRS_AddressMode v, eRS_AddressMode w)
{
	if (m_eU == u && m_eV == v && m_eW == w) return;
	m_eU = u;
	m_eV = v;
	m_eW = w;
	m_bDirty = true;
}

void RS_SampleState::SetMipLodBais(float lod)
{
	if (m_fMipLodBais == lod) return;
	m_fMipLodBais = lod;
	m_bDirty = true;
}

void RS_SampleState::SetMaxAniso(float aniso)
{
	if (m_fMaxAniso == aniso) return;
	m_fMaxAniso = aniso;
	m_bDirty = true;
}

void RS_SampleState::SetCompareFunc(eRS_ComparisonFunction compareFun)
{
	if (m_eCompareFun == compareFun) return;
	m_eCompareFun = compareFun;
	m_bDirty = true;
}

HRESULT RS_SampleState::DoState(iRS_Renderer * pRenderer)
{
	RS_RendererDX11* pRendererDX11 = Cast2RendererDX11(pRenderer);
	if (!pRendererDX11) return E_FAIL;
	ID3D11DeviceContext* pContext = pRendererDX11->GetContext();
	ID3D11Device* pDevice = pRendererDX11->GetDevice();
	if (!pContext || !pDevice) return E_FAIL;
	if (!m_pSamplerState || m_bDirty) {
		if (m_pSamplerState) {
			m_pSamplerState->Release();
			m_pSamplerState = nullptr;
		}
		m_bDirty = false;
		D3D11_SAMPLER_DESC descSampler;
		descSampler.Filter = cast2D3DFilter(m_eFilter);
		descSampler.AddressU = cast2D3DTextureAddressMode(m_eU);
		descSampler.AddressV = cast2D3DTextureAddressMode(m_eV);
		descSampler.AddressW = cast2D3DTextureAddressMode(m_eW);
		descSampler.MipLODBias = m_fMipLodBais;
		descSampler.MaxAnisotropy = (UINT)m_fMaxAniso;
		descSampler.ComparisonFunc = cast2D3DComparisonFunc(m_eCompareFun);
		descSampler.BorderColor[0] = descSampler.BorderColor[1] = descSampler.BorderColor[2] = descSampler.BorderColor[3] = 0.0f;
		descSampler.MinLOD = 0;
		descSampler.MaxLOD = 16;
		if (FAILED(pDevice->CreateSamplerState(&descSampler, &m_pSamplerState))) {
			printf("creating samplerState fails \n");
			return E_FAIL;
		}
	}
	//SamplerState 的DoState不会直接加入管线，而是在Shader中被使用
	return S_OK;
}

D3D11_FILTER RS_SampleState::cast2D3DFilter(eRS_Filter eFilter)
{
	D3D11_FILTER d3dFilter;
	switch (eFilter)
	{
	case eRS_Nearest:
		d3dFilter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		break;
	case eRS_Linear:
		d3dFilter = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
		break;
	case eRS_Bilinear:
		d3dFilter = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
		break;
	case eRS_Trilinear:
		d3dFilter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		break;
	case eRS_Blinear_Aniso:
		d3dFilter = D3D11_FILTER_ANISOTROPIC;
		break;
	case eRS_Trilinear_Aniso:
		d3dFilter = D3D11_FILTER_ANISOTROPIC;
		break;
	default:
		d3dFilter = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
		break;
	}
	return d3dFilter;
}

D3D11_TEXTURE_ADDRESS_MODE RS_SampleState::cast2D3DTextureAddressMode(eRS_AddressMode eAddressMode)
{
	D3D11_TEXTURE_ADDRESS_MODE d3dTexAddrMode;
	switch (eAddressMode)
	{
	case eRS_Wrap:
		d3dTexAddrMode = D3D11_TEXTURE_ADDRESS_WRAP;
		break;
	case eRS_Clamp:
		d3dTexAddrMode = D3D11_TEXTURE_ADDRESS_CLAMP;
		break;
	case eRS_Border:
		d3dTexAddrMode = D3D11_TEXTURE_ADDRESS_BORDER;
		break;
	default:
		d3dTexAddrMode = D3D11_TEXTURE_ADDRESS_WRAP;
		break;
	}
	return d3dTexAddrMode;

}

D3D11_COMPARISON_FUNC RS_SampleState::cast2D3DComparisonFunc(eRS_ComparisonFunction eCompareFun)
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
