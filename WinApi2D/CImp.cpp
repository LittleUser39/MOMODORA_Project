#include "framework.h"
#include "CImp.h"
#include "CCollider.h"

#include "CD2DImage.h"
#include "CAnimator.h"

#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"
#include "CAttState.h"

#include "CGravity.h"
#include "CRigidBody.h"

#include "CDagger.h"
#include "CKaho.h"

CImp::CImp()
{
	
	m_tInfo.fSpeed			= 130.f;
	m_tInfo.fHP				= 15.f;
	m_tInfo.fRecogRange		= 60.f;
	m_tInfo.fAttRange		= 130.f;
	m_tInfo.fAtt			= 3.f;
	
	m_eCurState = MON_STATE::IDLE;
	bAttcking = false;

	SetName(L"Imp");
	SetScale(fPoint(40.f, 40.f));

	CreateCollider();
	GetCollider()->SetScale(fPoint(40.f, 40.f));

	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"sImp", L"texture\\sImp_0.png");
	m_pImg2 = CResourceManager::getInst()->LoadD2DImage(L"sImpAtt", L"texture\\sImpThrow_Full.png");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"sImpIdleR", m_pImg, fPoint(0,0), fPoint(32.f,32.f), fPoint(0,0), 1.f, 1, true);
	GetAnimator()->CreateAnimation(L"sImpIdleL", m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(0, 0), 1.f, 1,true,true);

	GetAnimator()->CreateAnimation(L"sImpAttR", m_pImg2, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 9, true);
	GetAnimator()->CreateAnimation(L"sImpAttL", m_pImg2, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 9, true, true);

	
	
	CreateGravity();
	CreateRigidBody();
}

CImp::~CImp()
{
}

CImp* CImp::Clone()
{
	return nullptr;
}

void CImp::render()
{
	component_render();
}

void CImp::update()
{
	update_move();
	update_state();
	update_animation();

	GetAnimator()->update();
	m_ePerState = m_eCurState;
}

void CImp::CreateDagger()
{
	//이게 그릴것 위치 정하는거
	fPoint fptpImp = GetPos();

	CDagger* mDagger = new CDagger;
	
	CKaho* pPlayer = CKaho::GetPlayer();
	fPoint fptPlayerPos = pPlayer->GetPos();

	fVec2 fvDiff = fptPlayerPos - fptpImp;
	
	if (0 > fvDiff.x)
	{
		fptpImp.x -= GetScale().x / 2.f;
		mDagger->SetPos(fptpImp);
		mDagger->SetDir(fPoint(-1.f, 0.f));
		mDagger->GetAnimator()->Play(L"ImpDaggerL");
	}
	else if (0 < fvDiff.x)
	{
		fptpImp.x += GetScale().x / 2.f;
		mDagger->SetPos(fptpImp);
		mDagger->SetDir(fPoint(1.f, 0.f));
		mDagger->GetAnimator()->Play(L"ImpDaggerR");
	}

	CreateObj(mDagger, GROUP_GAMEOBJ::MISSILE_MONSTER);
}

void CImp::update_move()
{
	m_fAttTime += fDT;

	if (m_eCurState==MON_STATE::ATT && m_fAttCoolTime <= m_fAttTime)
	{
		m_fAttTime = 0;
		CreateDagger();
	}
}

void CImp::update_state()
{

	fPoint fpImp = GetPos();
	CKaho* pPlayer = CKaho::GetPlayer();
	fPoint fptPlayerPos = pPlayer->GetPos();
	fVec2 fvDiff = fptPlayerPos - fpImp;
	float fLen = fvDiff.Length();

	if (fLen > m_tInfo.fAttRange)
	{
		m_eCurState = MON_STATE::IDLE;
	}
	else if (fLen < m_tInfo.fAttRange)
	{
		m_eCurState = MON_STATE::ATT;
		bAttcking = true;
	}
}

void CImp::update_animation()
{
	fPoint fpImp = GetPos();
	CKaho* pPlayer = CKaho::GetPlayer();
	fPoint fptPlayerPos = pPlayer->GetPos();
	fVec2 fvDiff = fptPlayerPos - fpImp;
	
	switch (m_eCurState)
	{
	case MON_STATE::IDLE:
	{
		if (0 < fvDiff.x)
		{
			GetAnimator()->Play(L"sImpIdleR");
		}
		else if (0 > fvDiff.x)
		{
			GetAnimator()->Play(L"sImpIdleL");
		}
		
	}
		break;
	case MON_STATE::ATT:
	{
		if (0 < fvDiff.x)
		{
			GetAnimator()->Play(L"sImpAttR");
		}
		else if (0 > fvDiff.x)
		{
			GetAnimator()->Play(L"sImpAttL");
		}
	}
		break;
	}
}

void CImp::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile_Player1" || pOtherObj->GetName() == L"Player_hitbox")
	{

		m_tInfo.fHP -= 1;
		if (m_tInfo.fHP <= 0)
			DeleteObj(this);
	}
}