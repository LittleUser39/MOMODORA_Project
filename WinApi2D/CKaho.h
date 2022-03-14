#pragma once
#include "CPlayer.h"
class CKaho : public CPlayer
{
private:
	CD2DImage* m_pImg;
	CD2DImage* m_pImg2;
	float m_fVelocity = 200;
public:
	CKaho();
	~CKaho();
	virtual CKaho* Clone();

	virtual void update();
	virtual void render();
};

