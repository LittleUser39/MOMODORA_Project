#pragma once
#include "CState.h"
class CAttState : public CState
{
	float m_fAttCoolTime = 1.f;
	float m_fAttTime = 0;

public:
	CAttState(MON_STATE state);
	virtual ~CAttState();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

