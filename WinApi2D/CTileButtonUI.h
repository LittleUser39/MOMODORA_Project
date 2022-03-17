#pragma once
#include "CButtonUI.h"
class CTileButtonUI : public CButtonUI
{
private:
	int m_iIdx;

public:
	CTileButtonUI();
	virtual ~CTileButtonUI();

	virtual void render();

	int GetIdx();
	void SetIdx(int idx);
};