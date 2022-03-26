#include "framework.h"
#include "CBState.h"
#include "BossAI.h"
#include "CFennel.h"

CBState::CBState(Boss_Pattern state)
{
	m_pOwnerAI = nullptr;
	m_eState = state;
}

CBState::~CBState()
{
}

BossAI* CBState::GetOwnerAI()
{
	return m_pOwnerAI;
}

Boss_Pattern CBState::GetType()
{
	return m_eState;
}

CFennel* CBState::GetMonster()
{
	return m_pOwnerAI->GetOwnerAI();
}