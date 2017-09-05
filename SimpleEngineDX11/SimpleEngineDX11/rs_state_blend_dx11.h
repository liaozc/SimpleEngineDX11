#ifndef RS_STATE_BLEND_DX11_H
#define RS_STATE_BLEND_DX11_H

#include <d3d11.h>
#include "rs_state_blend_public.h"

class RS_BlendStateDX11 : public iRS_BlendState
{
public:
	RS_BlendStateDX11();
	virtual ~RS_BlendStateDX11();
	virtual HRESULT DoState(iRS_Renderer* pRenderer);
	virtual BlendCongfig GetBlendConfig() const { return m_sBlendConfig; }
	virtual void SetBlendConfig(const BlendCongfig& config);
	virtual void SetBlendState(eRS_BlendOption src, eRS_BlendOption dst);

protected:
	D3D11_BLEND cast2DX11BlendFormat(eRS_BlendOption option);
	BlendCongfig m_sBlendConfig;
	ID3D11BlendState* m_pBlendState;
	bool m_bDirty;
};

#endif
