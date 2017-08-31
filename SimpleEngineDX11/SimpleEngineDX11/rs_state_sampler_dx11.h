#ifndef RS_STATE_SAMPLE_DX11_H
#define RS_STATE_SAMPLE_DX11_H

#include <d3d11.h>
#include "rs_state_sampler_public.h"

class RS_SampleState : public iRS_SamplerState
{
public:
	RS_SampleState();
	virtual void SetFilter(eRS_Filter filter);
	virtual eRS_Filter GetFilter() const { return m_eFilter; }
	virtual void SetAddressMode(eRS_AddressMode u, eRS_AddressMode v, eRS_AddressMode w);
	virtual void SetMipLodBais(float lod);
	virtual void SetMaxAniso(float aniso);
	virtual void SetCompareFunc(eRS_ComparisonFunction compareFun);
	virtual HRESULT DoState(iRS_Renderer* pRenderer);
protected:
	D3D11_FILTER cast2D3DFilter(eRS_Filter eFilter);
	D3D11_TEXTURE_ADDRESS_MODE cast2D3DTextureAddressMode(eRS_AddressMode eAddressMode);
	D3D11_COMPARISON_FUNC cast2D3DComparisonFunc(eRS_ComparisonFunction eCompareFun);

protected:
	eRS_Filter m_eFilter;
	eRS_AddressMode m_eU;
	eRS_AddressMode m_eV;
	eRS_AddressMode m_eW;
	float m_fMipLodBais;
	float m_fMaxAniso;
	eRS_ComparisonFunction m_eCompareFun;
	bool m_bDirty;
	ID3D11SamplerState* m_pSamplerState;
	
};


#endif
