#include "framework.h"
#include "CTraceState.h"
#include "CKaho.h"
#include "CMonster.h"
#include "CAnimator.h"

CTraceState::CTraceState(MON_STATE state) : CState(state)
{
}

CTraceState::~CTraceState()
{
}

void CTraceState::update()
{
	CKaho* pPlayer = CKaho::GetPlayer();
	if (nullptr == pPlayer)
		return;

	fPoint fptPlayerPos = pPlayer->GetPos();

	CMonster* pMonster = GetMonster();
	fPoint fptMonsterPos = pMonster->GetPos();

	fVec2 fvDiff = fptPlayerPos - fptMonsterPos;
	float fLen = fvDiff.Length();

	if (fLen >= pMonster->GetMonInfo().fRecogRange)
	{
		ChangeAIState(GetOwnerAI(), MON_STATE::IDLE);
	}
	else if (fLen < pMonster->GetMonInfo().fAttRange)
	{
		ChangeAIState(GetOwnerAI(), MON_STATE::ATT);
	}
	fPoint pos = pMonster->GetPos();
	pos += fvDiff.normalize() * 100 * fDT;
	pMonster->SetPos(pos);
	
	if (0 < fvDiff.x)
		pMonster->GetAnimator()->Play(L"sMonkey_FullR");
	else if (0 > fvDiff.x)
		pMonster->GetAnimator()->Play(L"sMonkey_FullL");

}

void CTraceState::Enter()
{
}

void CTraceState::Exit()
{
}