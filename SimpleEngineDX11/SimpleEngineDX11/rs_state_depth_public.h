#ifndef RS_STATE_DEPTH_PUBLIC_H
#define RS_STATE_DEPTH_PUBLIC_H

#include "rs_state_public.h"
#include "data_type.h"

enum eRS_DepthStencilOperation
{	
	eRS_Keep,
	eRS_Set_Zero,
	eRS_Replace,
	eRS_Invert,
	eRS_Incr,
	eRS_Decr,
	eRS_Incr_Sat,
	eRS_Decr_Sat,
	eRS_StencilOperation_Count,
};

class iRS_DepthState : public iRS_State
{
public:
	virtual eRS_StateType GetType() const { return eRS_StateType_Depth; }
	virtual void SetDepthTest(bool enable) = 0;
	virtual bool GetDepthTest() const = 0;
	virtual void SetStencilTest(bool enable) = 0;
	virtual bool GetStencilTest() const = 0;
	virtual void SetDepthWriteEnable(bool enable) = 0;
	virtual bool GetDepthWirteEnable() const = 0;
	virtual void SetStencilWriteMask(byte mask) = 0;
	virtual unsigned char GetStencilWriteMask() const = 0;
	virtual void SetStencilReadMask(byte mask) = 0;
	virtual unsigned char GetStencilReadMask() const = 0;
	virtual void SetDepthFunc(eRS_ComparisonFunction depthfunc) = 0;
	virtual eRS_ComparisonFunction GetDepthFunc() const = 0;
	virtual void SetStencilFunc(eRS_ComparisonFunction stencilfunc) = 0;
	virtual eRS_ComparisonFunction GetStencilFunc() const = 0;
	virtual void SetStencilFail(eRS_DepthStencilOperation operation) = 0;
	virtual void SetStencilPass(eRS_DepthStencilOperation operation) = 0;
	virtual void SetDepthlFail(eRS_DepthStencilOperation operation) = 0;
	virtual eRS_DepthStencilOperation GetStencilFail() const = 0;
	virtual eRS_DepthStencilOperation GetStencilPass() const = 0;
	virtual eRS_DepthStencilOperation GetDepthlFail() const = 0;
	virtual ~iRS_DepthState() {}
};

#endif
