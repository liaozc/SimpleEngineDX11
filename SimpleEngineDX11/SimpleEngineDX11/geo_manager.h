#ifndef GEO_MANAGER_H
#define GEO_MANAGER_H

#include "geo_manager_public.h"
#include "geo_mesh.h"

class GeometryManager : public iGEO_Manager
{
public:
	virtual Mesh* CreateMesh(void* pVertData, int nVertSize, UINT16 nVertStride, void* pInds, int nIndexSize, UINT16 nIndexStride, eRS_VertDataFormat* pFormat, UINT16 nFormatSize);

};

#endif