#include "framework.h"
#include "CHitBox.h"
#include "CCollider.h"
#include "CKaho.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CD2DImage.h"

CHitBox* CHitBox::Clone()
{
	return new CHitBox(*this);
}

CHitBox::CHitBox()
{
	m_pOwner = nullptr;
	m_fDelay = 0;
	SetName(L"Player_hitbox");
	SetScale(fPoint(70.f, 60.f));
	CreateCollider();
	GetCollider()->SetScale(fPoint(70.f, 60.f));
	
	//todo 이미지 변수 이름 바꾸기 
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"AttEffect", L"texture\\AttEffect.png");
	m_pImg2 = CResourceManager::getInst()->LoadD2DImage(L"AttEffect2", L"texture\\AttEffect2.png");
	m_pImg3 = CResourceManager::getInst()->LoadD2DImage(L"AttEffect3", L"texture\\AttEffect3.png");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"AttEffectR", m_pImg, fPoint(0.f, 0.f), fPoint(96.f, 48.f), fPoint(96.f, 0), 0.05f, 6, false);
	GetAnimator()->CreateAnimation(L"AttEffectL", m_pImg, fPoint(0.f, 0.f), fPoint(96.f, 48.f), fPoint(96.f, 0), 0.05f, 6, false, true);
	GetAnimator()->CreateAnimation(L"AttEffect2R", m_pImg2, fPoint(0.f, 0.f), fPoint(96.f, 48.f), fPoint(96.f, 0), 0.05f, 6, false);
	GetAnimator()->CreateAnimation(L"AttEffect2L", m_pImg2, fPoint(0.f, 0.f), fPoint(96.f, 48.f), fPoint(96.f, 0), 0.05f, 6, false, true);
	GetAnimator()->CreateAnimation(L"AttEffect3R", m_pImg3, fPoint(0.f, 0.f), fPoint(96.f, 48.f), fPoint(96.f, 0), 0.05f, 8, false);
	GetAnimator()->CreateAnimation(L"AttEffect3L", m_pImg3, fPoint(0.f, 0.f), fPoint(96.f, 48.f), fPoint(96.f, 0), 0.05f, 8, false, true);

}

CHitBox::~CHitBox()
{
	
}

void CHitBox::update()
{
	m_fDelay += fDT;

	update_animation();

	GetAnimator()->update();
	
	//일정 시간있다가 삭제
	if (m_fDelaytime + 0.1f <= m_fDelay)
		DeleteObj(this);
}

void CHitBox::render()
{
	component_render();
}

void CHitBox::update_animation()
{
	switch (m_pOwner->GetAttCount())
	{
	case 1:
	{
		if(1 == m_pOwner->GetDirect())
			GetAnimator()->Play(L"AttEffectR");
		else if(-1==m_pOwner->GetDirect())
			GetAnimator()->Play(L"AttEffectL");
	}
	break;

	case 2:
	{
		if (1 == m_pOwner->GetDirect())
			GetAnimator()->Play(L"AttEffect2R");
		else if (-1 == m_pOwner->GetDirect())
			GetAnimator()->Play(L"AttEffect2L");
	}
	break;

	case 3:
	{
		if (1 == m_pOwner->GetDirect())
			GetAnimator()->Play(L"AttEffect3R");
		else if (-1 == m_pOwner->GetDirect())
			GetAnimator()->Play(L"AttEffect3L");
	}
	break;
	}	
}
 
void CHitBox::OnCollisionEnter(CCollider* pOther)
{

}

CKaho* CHitBox::GetOwnerObj()
{
	return m_pOwner;
}

void CHitBox::SetOwnerObj(CKaho* pOwner)
{
	m_pOwner = pOwner;
}
