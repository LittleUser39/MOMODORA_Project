#include "framework.h"
#include "BossAI.h"
#include "CBState.h"

BossAI::BossAI()
{
	m_pOwner = nullptr;
	m_pCurState = nullptr;
}

BossAI::~BossAI()
{
	for (map<Boss_Pattern, CBState*>::iterator iter = m_mapState.begin(); iter != m_mapState.end(); iter++)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}
	m_mapState.clear();
}

void BossAI::update()
{
	m_pCurState->update();
}

CBState* BossAI::GetState(Boss_Pattern state)
{
	map<Boss_Pattern, CBState*>::iterator iter = m_mapState.find(state);
	if (m_mapState.end() == iter)
	{
		return nullptr;
	}
	return iter->second;
}

CFennel* BossAI::GetOwnerAI()
{
	return m_pOwner;
}

void BossAI::SetCurState(Boss_Pattern state)
{
	m_pCurState = GetState(state);
	assert(m_pCurState);
}

void BossAI::AddState(CBState* state)
{
	CBState* pState = GetState(state->GetType());
	assert(!pState);

	m_mapState.insert(make_pair(state->GetType(), state));
	state->m_pOwnerAI = this;
}

void BossAI::ChangeState(Boss_Pattern nextState)
{
	CBState* pNextState = GetState(nextState);
	assert(m_pCurState != pNextState);

	m_pCurState->Exit();
	m_pCurState = pNextState;
	m_pCurState->Enter();
}