#include "framework.h"
#include "CSelectButton.h"
#include "CD2DImage.h"


CSelectButton::CSelectButton()
{
	m_iIdx = 0;
}

CSelectButton::~CSelectButton()
{
}

CSelectButton* CSelectButton::Clone()
{
	return new CSelectButton(*this);
}

void CSelectButton::render()
{
	if (nullptr != m_pImg)
	{
		UINT iWidth = m_pImg->GetWidth();
		UINT iHeight = m_pImg->GetHeight();

		UINT iMaxRow = iHeight;
		UINT iMaxCol = iWidth;

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

int CSelectButton::GetIdx()
{
	return m_iIdx;
}

void CSelectButton::SetIdx(int idx)
{
	m_iIdx = idx;
}
