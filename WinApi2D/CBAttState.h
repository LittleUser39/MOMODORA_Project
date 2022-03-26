#pragma once
#include "CBState.h"
class CBAttState :
    public CBState
{
	bool m_bCanAtt;
	float b_fDT;

private:
	float m_fAttCoolTime = 1.f;
	float m_fAttTime = 0;

public:
	CBAttState(Boss_Pattern state);
	virtual ~CBAttState();
	
	virtual void update();
	virtual void Enter();
	virtual void Exit();
	
};

