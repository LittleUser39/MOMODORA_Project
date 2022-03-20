#include "framework.h"
#include "CHitBox.h"
#include "CCollider.h"
#include "CKaho.h"

CHitBox* CHitBox::Clone()
{
	return new CHitBox(*this);
}

CHitBox::CHitBox()
{
	m_fvDir = fVec2(0, 0);
	m_pOwner = nullptr;
	SetName(L"HitBox_Player");

	CreateCollider();
	GetCollider()->SetScale(fPoint(60.f, 50.f));
}

CHitBox::~CHitBox()
{
	
}

void CHitBox::update()
{
	
}

void CHitBox::render()
{
	fPoint pos = GetPos();
	fPoint scale = GetScale();

	fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(pos);

	CRenderManager::getInst()->RenderEllipse(
		(fptRenderPos.x),
		(fptRenderPos.y),
		(scale.x / 2.f),
		(scale.y / 2.f));

	component_render();
}

CGameObject* CHitBox::GetOwnerObj()
{
	return m_pOwner;
}

void CHitBox::SetOwnerObj(CGameObject* pOwner)
{
	m_pOwner = pOwner;
}



void CHitBox::create()
{
	CGameObject* ownerObj = GetOwnerObj();
	if (ownerObj == nullptr) return;

	
	CKaho* user = dynamic_cast<CKaho*>(ownerObj);

	if (nullptr != user)
	{
		//히트박스 유저위치로 방향 설정
		SetPos(user->GetPos());
		//오른쪽
		if (user->GetDirect() > 0)
		{
			GetCollider()->SetFinalPos(GetPos());
			GetCollider()->SetOffsetPos(fPoint(30.f, 10.f));
		}
		//왼쪽
		else
		{
			GetCollider()->SetFinalPos(GetPos());
			GetCollider()->SetOffsetPos(fPoint(-30.f, 10.f));
		}
	}
}

void CHitBox::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();
	if (pOtherObj->GetName() == L"Monster")
	{

	}
}
