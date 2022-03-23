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
	
	MON_STATE::IDLE;

	SetName(L"Imp");
	SetScale(fPoint(40.f, 40.f));

	CreateCollider();
	GetCollider()->SetScale(fPoint(40.f, 40.f));

	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"sImp", L"texture\\sImp_0.png");
	
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"sImp", m_pImg, fPoint(), fPoint(), fPoint(), 1.f, 1, true);


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
}

void CImp::update()
{
}

void CImp::OnCollisionEnter(CCollider* pOther)
{
}

void CImp::CreateDagger()
{
	//이게 그릴것 위치 정하는거
	fPoint fpImp = this->GetPos();
	fPoint 
	CDagger* mDagger = new CDagger;
	
	CKaho* pPlayer = CKaho::GetPlayer();
	fPoint fptPlayerPos = pPlayer->GetPos();


	fVec2 fvDiff = fptPlayerPos - fpImp;

	if (0 > fvDiff.x)
		fpHitbox.x -= GetScale().x / 2.f;
	else if (0 < fvDiff.x)
		fpHitbox.x += GetScale().x / 2.f;

	CreateObj(mHitbox, GROUP_GAMEOBJ::MISSILE_MONSTER);
}

void CImp::update_move()
{
}

void CImp::update_state()
{
}

void CImp::update_animation()
{
}
