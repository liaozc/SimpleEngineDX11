#include "geo_mesh.h"


Mesh::Mesh(void * pVertData, int nVertSize, UINT16 nVertStride, void * pInds, int nIndexSize, UINT16 nIndexStride, eRS_VertDataFormat* pFormat, UINT16 nFormatSize)
	: m_pVertData(pVertData), m_nVertSize(nVertSize), m_nVStride(nVertStride),
	m_pIndexData(pInds), m_nIndexSize(nIndexSize), m_nIStride(nIndexStride),
	m_pFormat(pFormat), m_nFormatSize(nFormatSize)
{
}
