#include "framework.h"
#include "CLight.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CD2DImage.h"
#include "CKaho.h"

CLight::CLight()
{
	SetScale(fPoint(32.f, 240.f));
	SetName(L"Missile_Boss");

	

	CreateCollider();
	GetCollider()->SetScale(fPoint(32.f, 240.f));

	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"SSunder", L"texture\\sLighting_Full.png");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Lighting", m_pImg, fPoint(0.f,0.f), fPoint(32.f,240.f), fPoint(32.f,0.f), 0.5f, 3, false);
	GetAnimator()->Play(L"Lighting");
}

CLight::~CLight()
{
}

CLight* CLight::Clone()
{
	return new CLight(*this);
}

void CLight::update()
{
	m_fDelay += fDT;
	//일정 시간있다가 삭제
	if (m_fDelaytime <= m_fDelay)
	{
		DeleteObj(this);
	}

	GetAnimator()->update();
}

void CLight::render()
{
	component_render();
}

void CLight::OnCollisionEnter(CCollider* pOther)
{
}
