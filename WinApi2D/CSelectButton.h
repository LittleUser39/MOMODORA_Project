#pragma once
#include "CButtonUI.h"
class CSelectButton : public CButtonUI
{
	int m_iIdx;

public:
	CSelectButton();
	virtual ~CSelectButton();

	virtual CSelectButton* Clone();

	virtual void render();

	int GetIdx();
	void SetIdx(int idx);
};

