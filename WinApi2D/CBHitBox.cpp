#include "framework.h"
#include "CBHitBox.h"
#include "CCollider.h"

CBHitBox::CBHitBox()
{
	m_pOwner = nullptr;
	SetName(L"Fennel_HitBox");
	SetScale(fPoint(60.f, 40.f));
	CreateCollider();
	GetCollider()->SetScale(fPoint(60.f, 40.f));
}

CBHitBox::~CBHitBox()
{
}

CBHitBox* CBHitBox::Clone()
{
	return nullptr;
}

void CBHitBox::update()
{
	m_fDelay += fDT;

	//일정 시간있다가 삭제
	if (m_fDelaytime + 0.1f <= m_fDelay)
		DeleteObj(this);
}

void CBHitBox::render()
{
	component_render();
}

void CBHitBox::OnCollisionEnter(CCollider* pOther)
{
}

CFennel* CBHitBox::GetOwnerObj()
{
	return m_pOwner;
}

void CBHitBox::SetOwnerObj(CFennel* pOwner)
{
	m_pOwner = pOwner;
}
