#ifndef RS_BUFFER_PUBLIC_H
#define RS_BUFFER_PUBLIC_H

#include "ref_public.h"

enum eRS_BufferType
{
	eRS_BT_None,
	eRS_BT_Vertex,
	eRS_BT_Index,
	eRS_BT_Constant,
	eRS_BT_Count,
};

class iRS_Buffer : public iRef
{
public:
	virtual eRS_BufferType GetType() const = 0;
	virtual HRESULT  Create(int dataSize, void* data) = 0;
	virtual ~iRS_Buffer() {}
};

#endif
