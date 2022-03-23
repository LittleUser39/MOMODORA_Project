#include "framework.h"
#include "CMHitBox.h"
#include "CCollider.h"

CMHitBox::CMHitBox()
{
	m_pOwner = nullptr;
	SetName(L"Monkey_HitBox");
	SetScale(fPoint(40.f, 40.f));
	CreateCollider();
	GetCollider()->SetScale(fPoint(40.f, 40.f));
}

CMHitBox::~CMHitBox()
{
}

CMHitBox* CMHitBox::Clone()
{
	return nullptr;
}

void CMHitBox::update()
{
	m_fDelay += fDT;

	//일정 시간있다가 삭제
	if (m_fDelaytime + 0.1f <= m_fDelay)
		DeleteObj(this);
}

void CMHitBox::render()
{
	component_render();
}

void CMHitBox::OnCollisionEnter(CCollider* pOther)
{
}

CMonster* CMHitBox::GetOwnerObj()
{
	return m_pOwner;
}

void CMHitBox::SetOwnerObj(CMonster* pOwner)
{
	m_pOwner = pOwner;
}
