#ifndef RS_BUFFER_PUBLIC_H
#define RS_BUFFER_PUBLIC_H

enum eRS_BufferType
{
	eRS_BufferType_Vertex,
	eRS_BufferType_Index,
	eRS_BufferType_Constant,
	eRS_BufferType_Count,
};

class iRS_Buffer
{
public:
	virtual eRS_BufferType GetType() const = 0;
	virtual void* Map2Memory(int& width,int& height) = 0;
	virtual void  Map2GPU() = 0;
	virtual HRESULT  Create(int dataSize, void* data) = 0;
};

#endif
