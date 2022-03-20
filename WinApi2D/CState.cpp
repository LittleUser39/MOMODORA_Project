#include "framework.h"
#include "CState.h"
#include "AI.h"
#include "CMonster.h"

CState::CState(MON_STATE state)
{
	m_pOwnerAI = nullptr;
	m_eState = state;
}

CState::~CState()
{
}

AI* CState::GetOwnerAI()
{
	return m_pOwnerAI;
}

MON_STATE CState::GetType()
{
	return m_eState;
}

CMonster* CState::GetMonster()
{
	return m_pOwnerAI->GetOwnerAI();
}