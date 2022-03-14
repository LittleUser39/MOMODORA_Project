#pragma once
#include "CPlayer.h"
class CKaho : public CPlayer
{
private:
	CD2DImage* m_pImg;
	float m_fVelocity = 300;
public:
	CKaho();
	~CKaho();
	virtual CKaho* Clone();

	virtual void update();
	virtual void render();
};

