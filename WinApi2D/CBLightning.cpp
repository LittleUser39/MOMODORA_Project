#include "framework.h"
#include "CBLightning.h"
#include "CKaho.h"
#include "CAnimator.h"
#include "CFennel.h"

CBLightning::CBLightning(Boss_Pattern state):CBState(state)
{

}

CBLightning::~CBLightning()
{

}

void CBLightning::update()
{
	CFennel* pBoss = GetMonster();

	if (m_bNext)
		ChangeBossAIState(GetOwnerAI(), Boss_Pattern::IDLE);


	pBoss->GetAnimator()->Play(L"FennelLightL");
	
	m_bfDT += fDT;
	if (3.f <= m_bfDT)
	{
		pBoss -> CreateLighting();
		m_bfDT = 0;
		m_bNext = true;
	}


}

void CBLightning::Enter()
{
	m_bNext = false;
}

void CBLightning::Exit()
{

}
