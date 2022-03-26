#pragma once
#include "CBState.h"
class CBIdleState : public CBState
{	
	float m_bfDT = 0;

	public:
		CBIdleState(Boss_Pattern state);
		virtual ~CBIdleState();

		virtual void update();
		virtual void Enter();
		virtual void Exit();


};


