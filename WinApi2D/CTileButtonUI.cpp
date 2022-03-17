#include "framework.h"
#include "CTileButtonUI.h"
#include "CD2DImage.h"
#include "CTile.h"

CTileButtonUI::CTileButtonUI()
{
	m_iIdx = 0;
}

CTileButtonUI::~CTileButtonUI()
{
}

void CTileButtonUI::render()
{
	if (nullptr != m_pImg)
	{
		UINT iWidth = m_pImg->GetWidth();
		UINT iHeight = m_pImg->GetHeight();

		UINT iMaxRow = iHeight / CTile::SIZE_TILE;
		UINT iMaxCol = iWidth / CTile::SIZE_TILE;

		UINT iCurRow = (m_iIdx / iMaxCol) % iMaxRow;
		UINT iCurCol = (m_iIdx % iMaxCol);


		CRenderManager::getInst()->RenderFrame(
			m_pImg,
			GetFinalPos().x,
			GetFinalPos().y,
			GetFinalPos().x + GetScale().x,
			GetFinalPos().y + GetScale().y,
			iCurCol * GetScale().x,
			iCurRow * GetScale().y,
			(iCurCol + 1) * GetScale().x,
			(iCurRow + 1) * GetScale().y
		);
	}
}

int CTileButtonUI::GetIdx()
{
	return m_iIdx;
}

void CTileButtonUI::SetIdx(int idx)
{
	m_iIdx = idx;
}
