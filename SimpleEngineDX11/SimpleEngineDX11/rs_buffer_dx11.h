#ifndef RS_BUFFER_DX11_H
#define RS_BUFFER_DX11_H

#include <d3d11.h>
#include "rs_buffer_public.h"

class iRS_Renderer;

class RS_BufferDX11 : public iRS_Buffer
{
public:
	RS_BufferDX11(eRS_BufferType bufferType, int dataSize, void* data,bool bStatic,iRS_Renderer* pRenderer);
	virtual eRS_BufferType GetType() const { return m_eType; }
	virtual void* Map2Memory(int& width,int& height);
	virtual void  Map2GPU();
	virtual HRESULT  Create(int dataSize, void* data);
protected:
	D3D11_BIND_FLAG getFlag() const;
protected:
	iRS_Renderer* m_pRenderer;
	eRS_BufferType m_eType;
	ID3D11Buffer* m_pBuffer;
	int m_nSize;
	bool m_bStatic;
};

#endif
