#ifndef REF_PUBLIC_H
#define REF_PUBLIC_H

#include "platform.h"

class iRef
{
public:
	iRef() :m_nRef(1)
	{
		static int m_id = 0; 
		m_localId = m_id++;
	
	}
	virtual void AddRef() 
	{
		m_nRef++;	
	}
	virtual void Release() 
	{
		Assert(m_nRef > 0);
		m_nRef--;
		if (m_nRef == 0) {
			delete this;
		}
	}
	virtual ~iRef() { 
#ifdef _DEBUG
		Assert(m_nRef == 0);
#endif
		printf("~iRef : %d\n", m_localId);
	}
protected:
	int m_nRef;
	int m_localId;
};

#define SAFE_RELEASE(pOBJ) if(pOBJ){pOBJ->Release();pOBJ = nullptr;}
#define SAFE_ADDREF(pOBJ) if(pOBJ){pOBJ->AddRef();}
#define SAFE_DELETE(pOBJ) if(pOBJ){ delete pOBJ;}
#define SAFE_DELETE_ARRAY(pArray) if(pArray){ delete[] pArray;}

#endif
