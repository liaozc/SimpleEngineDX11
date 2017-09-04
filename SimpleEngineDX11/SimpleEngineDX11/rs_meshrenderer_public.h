#ifndef RS_MESHRENDERER_PUBLIC_H
#define RS_MESHRENDERER_PUBLIC_H 

class Mesh;
class iRS_Material;
class iRS_Buffer;
class iRS_Renderer;

class iRS_MeshRenderer
{
public:	
	virtual void SetMesh(Mesh* mesh) = 0;
	virtual Mesh* GetMesh() const = 0;
	virtual iRS_Material* GetMaterial() const = 0;
	virtual void SetMaterial(iRS_Material* pMat) = 0;
	virtual iRS_Buffer* GetVertBuffer() const = 0;
	virtual iRS_Buffer* GetIndexBuffer() const = 0;
	virtual void DoRender() = 0;
};

#endif