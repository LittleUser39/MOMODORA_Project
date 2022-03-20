#include "framework.h"
#include "CAttState.h"
#include "CKaho.h"
#include "CMonster.h"
#include "CD2DImage.h"
#include "CAnimator.h"

CAttState::CAttState(MON_STATE state):CState(state)
{



}

CAttState::~CAttState()
{

}

void CAttState::update()
{
	CKaho* pPlayer = CKaho::GetPlayer();
	if (nullptr == pPlayer)
		return;

	fPoint fptPlayerPos = pPlayer->GetPos();

	CMonster* pMonster = GetMonster();
	fPoint fptMonsterPos = pMonster->GetPos();

	fVec2 fvDiff = fptPlayerPos - fptMonsterPos;
	float fLen = fvDiff.Length();
	if (fLen >= pMonster->GetMonInfo().fAttRange)
	{
		ChangeAIState(GetOwnerAI(), MON_STATE::IDLE);
	}

	

	fPoint pos = pMonster->GetPos();
	pos += fvDiff.normalize() * 100 * fDT;
	pMonster->SetPos(pos);
}

void CAttState::Enter()
{

}

void CAttState::Exit()
{

}
