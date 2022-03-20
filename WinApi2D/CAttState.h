#pragma once
#include "CState.h"
class CAttState : public CState
{
public:
	CAttState(MON_STATE state);
	virtual ~CAttState();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

