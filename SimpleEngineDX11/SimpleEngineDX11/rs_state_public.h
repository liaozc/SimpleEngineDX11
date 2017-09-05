#ifndef RS_STATE_PUBLIC_H
#define RS_STATE_PUBLIC_H

#include "ref_public.h"
#include "data_type.h"
class iRS_Renderer;

class iRS_State : public iRef
{
public:
	virtual eRS_StateType GetType() const = 0;
	virtual HRESULT DoState(iRS_Renderer* pRenderer) = 0;
	virtual ~iRS_State() {}
};

#endif
