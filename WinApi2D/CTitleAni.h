#pragma once
#include "CGameObject.h"

class CD2DImage;

class CTitleAni : public CGameObject
{
	CD2DImage* m_pImg;
public:
	CTitleAni();
	~CTitleAni();

	virtual CTitleAni* Clone();

	virtual void update();
	virtual void render();
};

