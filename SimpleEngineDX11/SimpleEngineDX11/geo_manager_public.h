#ifndef GEO_MANAGER_PUBLIC_H
#define GEO_MANAGER_PUBLIC_H

#include "geo_mesh.h"

class iGEO_Manager
{
public:
	virtual Mesh* CreateMesh(void* pVertData, int nVertSize, UINT16 nVertStride, void* pInds, int nIndexSize, UINT16 nIndexStride, eRS_VertDataFormat* pFormat, UINT16 nFormatSize) = 0;

};

#endif