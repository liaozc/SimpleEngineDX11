#ifndef RS_STATE_SAMPLE_PUBLIC_H
#define RS_STATE_SAMPLE_PUBLIC_H

#include "rs_state_public.h"
#include "data_type.h"

enum eRS_Filter
{
	eRS_Nearest,
	eRS_Linear,
	eRS_Bilinear,
	eRS_Trilinear,
	eRS_Blinear_Aniso,
	eRS_Trilinear_Aniso,
	eRS_Filter_Count,
};

enum eRS_AddressMode
{
	eRS_Wrap,
	eRS_Clamp,
	eRS_Border,
	eRS_AddressMode_Count,
};

class iRS_SamplerState : public iRS_State
{
public:
	virtual eRS_StateType GetType() const { return eRS_StateType_Sampler; }
	virtual void SetFilter(eRS_Filter filter) = 0;
	virtual eRS_Filter GetFilter() const = 0;
	virtual void SetAddressMode(eRS_AddressMode u, eRS_AddressMode v, eRS_AddressMode w) = 0;
	virtual void SetMipLodBais(float lod) = 0;
	virtual void SetMaxAniso(float aniso) = 0;
	virtual void SetCompareFunc(eRS_ComparisonFunction compareFun) = 0;
};

#endif
