#include "framework.h"
#include "CAttState.h"
#include "CKaho.h"
#include "CMonster.h"
#include "CD2DImage.h"
#include "CAnimator.h"
#include "CHitBox.h"

CAttState::CAttState(MON_STATE state):CState(state)
{

}

CAttState::~CAttState()
{

}

void CAttState::update()
{

	m_fAttTime += fDT;
	if (m_fAttTime >= m_fAttCoolTime)
		ChangeAIState(GetOwnerAI(), MON_STATE::IDLE);
}

void CAttState::Enter()
{

}

void CAttState::Exit()
{

}
