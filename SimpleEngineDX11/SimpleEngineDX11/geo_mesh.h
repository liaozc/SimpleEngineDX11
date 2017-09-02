#ifndef GEO_MESH_H
#define GEO_MESH_H

#include "platform.h"
#include "mth_math.h"
#include "data_type.h"

class Mesh
{
public:
	Mesh(void* pVertData,int nVertSize, UINT16 nVertStride,void* pInds, int nIndexSize, UINT16 nIndexStride, eRS_VertDataFormat* pFormat, UINT16 nFormatSize);
	eRS_VertDataFormat* GetFormat() const { return m_pFormat; }
	int GetFormatSize() const { return m_nFormatSize; }
	void* GetVerts() const { return m_pVertData; }
	void* GetInds() const { return m_pIndexData; }
	int GetVertSize() const { return m_nVertSize; }
	int GetIndexSize() const { return m_nIndexSize; }
	int GetVertStride() const { return m_nVStride; }
	int GetIndsStride() const { return m_nIStride; }
protected:
	void* m_pVertData;
	void* m_pIndexData;
	UINT16 m_nVStride;
	UINT16 m_nIStride;
	int m_nVertSize;
	int m_nIndexSize;
	eRS_VertDataFormat* m_pFormat;
	unsigned short m_nFormatSize;
};

#endif
