#include "geo_mesh.h"

Mesh::Mesh(Vector3 * pVerts, int nVertSize, void * pInds, byte indexType, int nIndexSize)
	:m_pVerts(pVerts),m_nVertSize(nVertSize),m_nIndexSize(nIndexSize)
{
	 if(indexType == 1)
		m_pInds_i = (int*)pInds;
	 else
		 m_pInds_s = (short*)pInds;
	 m_cIndexType = indexType;
}
