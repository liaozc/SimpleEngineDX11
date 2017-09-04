#include "geo_manager.h"

Mesh * GeometryManager::CreateMesh(void * pVertData, int nVertSize, UINT16 nVertStride, void * pInds, int nIndexSize, UINT16 nIndexStride, eRS_VertDataFormat * pFormat, UINT16 nFormatSize)
{
	return new Mesh(pVertData, nVertSize, nVertStride, pInds, nIndexSize, nIndexStride, pFormat, nFormatSize);
}
