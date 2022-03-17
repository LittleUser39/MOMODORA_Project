#include "framework.h"
#include "CImageObject.h"

CImageObject::CImageObject()
{
	m_pimg = nullptr;
}

CImageObject::~CImageObject()
{
}

CImageObject* CImageObject::Clone()
{
	return nullptr;
}

void CImageObject::render()
{
	if (nullptr == m_pimg)
		return;

	CRenderManager::getInst()->RenderImage(m_pimg,
		GetPos().x,
		GetPos().y,
		GetPos().x + GetScale().x,
		GetPos().y + GetScale().y);
}

void CImageObject::update()
{
}

void CImageObject::Load(const wstring& strKey, const wstring& strPath)
{
	m_pimg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
}
