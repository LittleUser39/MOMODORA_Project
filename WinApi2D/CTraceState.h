#pragma once
#include "CState.h"
class CTraceState : public CState
{
public:
	CTraceState(MON_STATE state);
	virtual ~CTraceState();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};