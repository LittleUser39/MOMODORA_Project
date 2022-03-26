#pragma once

class BossAI;
class CFennel;

class CBState
{
	friend class BossAI;

private:
	BossAI* m_pOwnerAI;
	Boss_Pattern m_eState;

public:
	CBState(Boss_Pattern state);
	virtual ~CBState();

	BossAI* GetOwnerAI();
	Boss_Pattern GetType();
	CFennel* GetMonster();


	virtual void update() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;


};
