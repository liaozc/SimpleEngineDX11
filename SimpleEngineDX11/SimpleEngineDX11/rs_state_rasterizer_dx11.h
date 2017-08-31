#ifndef RS_STATE_RASTERIZER_DX11_H
#define RS_STATE_RASTERIZER_DX11_H

#include <d3d11.h>
#include "rs_state_rasterizer_public.h"

class RS_RasterizerStateDX11 :public iRS_RasterizerState
{
public:
	RS_RasterizerStateDX11();
	virtual eRS_CullType GetCullType() const { return m_eCullType; }
	virtual void SetCullType(eRS_CullType cullType);
	virtual void SetFillMode(eRS_FillMode fillMode);
	virtual eRS_FillMode GetFillMode() const { return m_eFillModel; }
	virtual void SetMultiSample(bool enable);
	virtual bool GetMultiSample() const { return m_bMutilSample; }
	virtual void SetScissor(bool enable);
	virtual bool GetScissor() const { return m_bScissor; }
	virtual void SetDepthBais(float depthBais);
	virtual float GetDepthBais() const { return m_fDepthBais; }
	virtual void SetSlopeDepthBais(float slopeDepthBais);
	virtual float GetSlopeDepthBais() const { return m_fSlopeDepthBais; }
	virtual HRESULT DoState(iRS_Renderer* pRenderer);
protected:
	D3D11_FILL_MODE cast2D3DFillMode(eRS_FillMode fillMode);
	D3D11_CULL_MODE cast2D3DCullMode(eRS_CullType cullType);
protected:
	eRS_CullType m_eCullType;
	eRS_FillMode m_eFillModel;
	bool m_bMutilSample;
	bool m_bScissor;
	float m_fDepthBais;
	float m_fSlopeDepthBais;
	bool m_bDirty;
	ID3D11RasterizerState* m_pRasterizerState;
};


#endif
