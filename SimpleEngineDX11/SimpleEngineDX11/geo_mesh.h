#ifndef GEO_MESH_H
#define GEO_MESH_H

#include "platform.h"
#include "mth_math.h"
#include "rs_dataType.h"

class Mesh
{
public:
	Mesh(Vector3* pVerts,int nVertSize,void* pInds,byte indexType,int nIndexSize);
	eVertDataFormat* GetFormat() const { return m_pFormat; }
	int GetFormatSize() const { return m_nFormatSize; }
	void* GetVerts() const { return m_pVertData; }
	void* GetInds() const { return m_pIndexData; }
	int GetVertSize() const { return m_nVertSize; }
	int GetIndexSize() const { return m_nIndexSize; }
	int GetVertStride() const { return m_sVStride; }
	int GetIndsStride() const { return m_sIStride; }
protected:
	void* m_pVertData;
	void* m_pIndexData;
	unsigned short m_sVStride;
	unsigned short m_sIStride;
	int m_nVertSize;
	int m_nIndexSize;
	eVertDataFormat* m_pFormat;
	int m_nFormatSize;
};

#endif
