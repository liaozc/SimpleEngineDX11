#ifndef RS_STATE_BLEND_PUBLIC_H
#define RS_STATE_BLEND_PUBLIC_H

#include "rs_state_public.h"

enum eRS_BlendOption
{
	eRS_Zero,
	eRS_One,
	eRS_Src_Color,
	eRS_One_Minus_Src_Color,
	eRS_Dst_Color,
	eRS_One_Minus_Dst_Color,
	eRS_Src_Alpha,
	eRS_One_Minus_Src_Alpha,
	eRS_Dst_Alpha,
	eRS_One_Minus_Dst_Alpha,
	eRS_Src_Alpha_Saturate,
	eRS_BlendOption_Count,
};

struct BlendCongfig
{
	eRS_BlendOption src;
	eRS_BlendOption dst;
	bool operator == (const BlendCongfig& config)
	{
		return src == config.src && dst == config.dst;
	}
};

class iRS_BlendState : public iRS_State
{
public:
	virtual eRS_StateType GetType() const { return eRS_StateType_Blend; }
	virtual BlendCongfig GetBlendConfig() const = 0;
	virtual void SetBlendConfig(const BlendCongfig& config) = 0;
	virtual void SetBlendState(eRS_BlendOption src, eRS_BlendOption dst) = 0;
};

#endif
