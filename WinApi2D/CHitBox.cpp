#include "framework.h"
#include "CHitBox.h"
#include "CCollider.h"

CHitBox* CHitBox::Clone()
{
	return new CHitBox(*this);
}

CHitBox::CHitBox()
{
	SetScale(fPoint(50.f, 50.f));
	m_fvDir = fVec2(0, 0);
	SetName(L"HitBox_Player");

	CreateCollider();
	GetCollider()->SetScale(fPoint(50.f, 50.f));
}

CHitBox::~CHitBox()
{
	
}

void CHitBox::update()
{
	fPoint pos = GetPos();

	SetPos(pos);

	if (pos.x < 0 || pos.x > WINSIZEX
		|| pos.y < 0 || pos.y > WINSIZEY)
		DeleteObj(this);
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

void CHitBox::SetDir(fVec2 vec)
{
	m_fvDir = vec.normalize();
}

void CHitBox::SetDir(float theta)
{
	m_fvDir.x = (float)cos(theta);
	m_fvDir.y = (float)sin(theta);
}

void CHitBox::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();
	if (pOtherObj->GetName() == L"Monster")
	{
		DeleteObj(this);
	}
}
