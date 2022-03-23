#include "framework.h"
#include "CIdleState.h"
#include "CKaho.h"
#include "CMonster.h"
#include "CAnimator.h"

CIdleState::CIdleState(MON_STATE state)
	: CState(state)
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::update()
{
	CKaho* pPlayer = CKaho::GetPlayer();
	if (nullptr == pPlayer)
		return;

	fPoint fptPlayerPos = pPlayer->GetPos();

	CMonster* pMonster = GetMonster();
	fPoint fptMonsterPos = pMonster->GetPos();

	fVec2 fvDiff = fptPlayerPos - fptMonsterPos;
	float fLen = fvDiff.Length(); 
	
	if (fLen <= pMonster->GetMonInfo().fRecogRange)
	{
		ChangeAIState(GetOwnerAI(), MON_STATE::TRACE);
	}
	
	if (0 < fvDiff.x)
		pMonster->GetAnimator()->Play(L"sMonkey_idleR");
	else if (0 > fvDiff.x)
		pMonster->GetAnimator()->Play(L"sMonkey_idleL");
}

void CIdleState::Enter()
{
}

void CIdleState::Exit()
{
}