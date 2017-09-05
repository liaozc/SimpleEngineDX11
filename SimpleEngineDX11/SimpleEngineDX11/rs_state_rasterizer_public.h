#ifndef RS_STATE_RASTERIZER_PUBLIC_H
#define RS_STATE_RASTERIZER_PUBLIC_H

#include "rs_state_public.h"

enum eRS_CullType
{
	eRS_CullBack,
	eRS_CullFront,
	eRS_CullNone,
	eRS_CullType_Count,
};

enum eRS_FillMode
{
	eRS_Solid,
	eRS_WireFrame,
	eRS_Count,
};

class iRS_RasterizerState : public iRS_State
{
public:
	virtual eRS_StateType GetType() const { return eRS_StateType_Rasterizer; }
	virtual eRS_CullType GetCullType() const = 0;
	virtual void SetCullType(eRS_CullType cullType) = 0;
	virtual void SetFillMode(eRS_FillMode fillMode) = 0;
	virtual eRS_FillMode GetFillMode() const = 0;
	virtual void SetMultiSample(bool enable) = 0;
	virtual bool GetMultiSample() const = 0;
	virtual void SetScissor(bool enable) = 0;
	virtual bool GetScissor() const = 0;
	virtual void SetDepthBais(float depthBais) = 0;
	virtual float GetDepthBais() const = 0;
	virtual void SetSlopeDepthBais(float slopeDepthBais) = 0;
	virtual float GetSlopeDepthBais() const = 0;
	virtual ~iRS_RasterizerState() {}
};

#endif
