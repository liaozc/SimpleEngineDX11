#ifndef RS_STATE_DEPTH_DX11_H
#define RS_STATE_DEPTH_DX11_H

#include <d3d11.h>
#include "rs_state_depth_public.h"

class RS_DepthStateDX11 : public iRS_DepthState
{
public:
	RS_DepthStateDX11();
	virtual ~RS_DepthStateDX11();
	virtual void SetDepthTest(bool enable);
	virtual bool GetDepthTest() const { return m_bDepthTest; }
	virtual void SetStencilTest(bool enable);
	virtual bool GetStencilTest() const { return m_bStencilTest; }
	virtual void SetStencilWriteMask(byte mask);
	virtual unsigned char GetStencilWriteMask() { return m_cWriteMask; }
	virtual void SetStencilReadMask(byte mask);
	virtual unsigned char GetStencilReadMask() const { return m_cReadMask; }
	virtual void SetDepthWriteEnable(bool enable);
	virtual bool GetDepthWirteEnable() const { return m_bDepthWrite; }
	virtual void SetDepthFunc(eRS_ComparisonFunction depthfunc);
	virtual eRS_ComparisonFunction GetDepthFunc() const { return m_eDepthFunc; }
	virtual void SetStencilFunc(eRS_ComparisonFunction stencilfunc);
	virtual eRS_ComparisonFunction GetStencilFunc() const { return m_eStencilFunc; }
	virtual void SetStencilFail(eRS_DepthStencilOperation operation);
	virtual void SetStencilPass(eRS_DepthStencilOperation operation);
	virtual void SetDepthlFail(eRS_DepthStencilOperation operation);
	virtual eRS_DepthStencilOperation GetStencilFail() const { return m_eDSOP_StencilFail; }
	virtual eRS_DepthStencilOperation GetStencilPass() const { return m_eDSOP_StencilPass; }
	virtual eRS_DepthStencilOperation GetDepthlFail() const { return m_eDSOP_DepthFail; }
	virtual HRESULT DoState(iRS_Renderer* pRenderer);
protected:
	D3D11_COMPARISON_FUNC cast2D3DComparisonFunc(eRS_ComparisonFunction eCompareFun);
	D3D11_STENCIL_OP cast2D3DStencilOP(eRS_DepthStencilOperation eOperation);

protected:
	bool m_bDepthTest;
	bool m_bStencilTest;
	bool m_bDepthWrite;
	byte m_cWriteMask;
	byte m_cReadMask;
	eRS_ComparisonFunction m_eDepthFunc;
	eRS_ComparisonFunction m_eStencilFunc;
	eRS_DepthStencilOperation m_eDSOP_StencilPass;
	eRS_DepthStencilOperation m_eDSOP_StencilFail;
	eRS_DepthStencilOperation m_eDSOP_DepthFail;
	bool m_bDirty;
	ID3D11DepthStencilState* m_pDepthState;
	
};


#endif
