#pragma once
#include "CBState.h"
class CBLightning :
    public CBState
{
	float m_bfDT = 0;
	bool m_bNext;

public:
	CBLightning(Boss_Pattern state);
	virtual ~CBLightning();

	virtual void update();
	virtual void Enter();
	virtual void Exit();

};

