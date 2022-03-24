#include "framework.h"
#include "CArrow.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CD2DImage.h"

CArrow* CArrow::Clone()
{
	return new CArrow(*this);
}

CArrow::CArrow()
{
	SetScale(fPoint(20.f, 20.f));
	m_fvDir = fVec2(0, 0);
	SetName(L"Missile_Player1");

	CreateCollider();
	GetCollider()->SetScale(fPoint(15.f, 15.f));

	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"Arrow", L"texture\\sSealProjectile_0.png");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"ArrowR",m_pImg,fPoint(0,0),fPoint(24.f,8.f),fPoint(0,0),1.f,1,true);
	GetAnimator()->CreateAnimation(L"ArrowL", m_pImg, fPoint(0, 0), fPoint(24.f, 8.f), fPoint(0, 0), 1.f, 1, true, true);

}

CArrow::~CArrow()
{
}

void CArrow::update()
{
	fPoint pos = GetPos();

	pos.x += m_fVelocity * m_fvDir.x * fDT;
	pos.y += m_fVelocity * m_fvDir.y * fDT;

	SetPos(pos);

	if (pos.x < 0 || pos.x > WINSIZEX
		|| pos.y < 0 || pos.y > WINSIZEY)
		DeleteObj(this);

	GetAnimator()->update();
}

void CArrow::render()
{
	component_render();
}

void CArrow::SetDir(fVec2 vec)
{
	m_fvDir = vec.normalize();
}

void CArrow::SetDir(float theta)
{
	m_fvDir.x = (float)cos(theta);
	m_fvDir.y = (float)sin(theta);
}

void CArrow::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();
	if (pOtherObj->GetName() == L"Monster")
	{
		DeleteObj(this);
	}
}
