#include "framework.h"
#include "CAttState.h"
#include "CKaho.h"
#include "CMonster.h"
#include "CD2DImage.h"
#include "CAnimator.h"
#include "CHitBox.h"
#include "CAnimator.h"
CAttState::CAttState(MON_STATE state):CState(state)
{

}

CAttState::~CAttState()
{

}

void CAttState::update() //위에는 설정 할려고 입력한거 if 문아래가 상태에 관한 행동 입력
{
	CKaho* pPlayer = CKaho::GetPlayer();
	if (nullptr == pPlayer)
		return;

	fPoint fptPlayerPos = pPlayer->GetPos();

	CMonster* pMonster = GetMonster();
	fPoint fptMonsterPos = pMonster->GetPos();

	fVec2 fvDiff = fptPlayerPos - fptMonsterPos;
	float fLen = fvDiff.Length();

	m_fAttTime += fDT;
	if (fLen > pMonster->GetMonInfo().fAttRange)
		ChangeAIState(GetOwnerAI(), MON_STATE::IDLE);

	//좌우 반전
	if (0 < fvDiff.x)
	{
		pMonster->GetAnimator()->Play(L"MonkeyAtt_fullR");
		if (m_fAttCoolTime <= m_fAttTime)
		{
			m_fAttTime = 0;
			pMonster->CreateHitBox();
		}
	}
	else if (0 > fvDiff.x)
	{
		pMonster->GetAnimator()->Play(L"MonkeyAtt_fullL");
		if (m_fAttCoolTime <= m_fAttTime)
		{
			m_fAttTime = 0;
			pMonster->CreateHitBox();
		}
	}
}

void CAttState::Enter()
{

}

void CAttState::Exit()
{

}
