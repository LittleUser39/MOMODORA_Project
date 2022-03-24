#pragma once

class CMonster;
class CState;
class CFennel;

class AI
{
	friend class CMonster;

private:
	map<MON_STATE, CState*> m_mapState;
	CMonster* m_pOwner;
	CState* m_pCurState;

public:
	AI();
	~AI();

	CMonster* GetOwnerAI();
	
	CState* GetState(MON_STATE state);
	void SetCurState(MON_STATE state);
	
	void update();

	void AddState(CState* state);
	void ChangeState(MON_STATE nextState);

};