#ifndef RS_STATE_PUBLIC_H
#define RS_STATE_PUBLIC_H

#include "data_type.h"
class iRS_Renderer;

class iRS_State
{
public:
	virtual eRS_StateType GetType() const = 0;
	virtual HRESULT DoState(iRS_Renderer* pRenderer) = 0;
};

#endif
