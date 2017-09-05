#ifndef RS_BUFFER_DX11_H
#define RS_BUFFER_DX11_H

#include <d3d11.h>
#include <d3dcompiler.h>
#include "rs_buffer_public.h"
#include "data_type.h"
#include "stl_containers.h"

class RS_RendererDX11;

class RS_BufferDX11 : public iRS_Buffer
{
public:
	RS_BufferDX11(RS_RendererDX11* pRenderer);
	virtual ~RS_BufferDX11();

	virtual eRS_BufferType GetType() const { return m_eType; }
	virtual HRESULT  Create(int dataSize, void* data);
	virtual ID3D11Buffer* GetGPUBuffer() const { return m_pBuffer; }

protected:
	virtual void unInit();
protected:
	D3D11_BIND_FLAG getFlag() const;
protected:
	RS_RendererDX11* m_pRenderer;
	eRS_BufferType m_eType;
	ID3D11Buffer* m_pBuffer;
	int m_nSize;
	bool m_bStatic;
};

class RS_VertBufferDX11 : public RS_BufferDX11
{
public:
	RS_VertBufferDX11(RS_RendererDX11* pRenderer);
	void SetStride(short nStride) { m_nStride = nStride; }
	short GetStride() const { return m_nStride; }
protected:
	short m_nStride;
};

class RS_IndexBufferDX11 : public RS_BufferDX11
{
public:
	RS_IndexBufferDX11(RS_RendererDX11* pRenderer);
	void SetStride(short nStride) { m_nStride = nStride; }
	short GetStride() const { return m_nStride; }
protected:
	short m_nStride;
};


struct RS_ShaderConstantVar
{
	LPCSTR szName;
	short nSize;	// for set check;
	void* data;
	void clear() { if (szName) delete szName; szName = nullptr; }
	
};
typedef std::vector<RS_ShaderConstantVar> t_ShaderConstantVarArray;

class RS_ConstantBufferDX11 : public RS_BufferDX11
{
public:
	RS_ConstantBufferDX11(RS_RendererDX11* pRenderer);
	virtual ~RS_ConstantBufferDX11();
	HRESULT CreateFromShader(ID3D11ShaderReflectionConstantBuffer* pRefl);
	bool SetValue(LPCSTR name,void* data,short size);
	void Apply();
	
protected:
	virtual void unInit();
protected:
	byte*	m_pConstantMem;
	t_ShaderConstantVarArray m_vConstants;
	bool m_bDirty;
	
};


#endif
