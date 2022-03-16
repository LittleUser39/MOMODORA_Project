#include "framework.h"
#include "CMissile.h"
#include "CArrow.h"
#include "CCollider.h"

CArrow* CArrow::Clone()
{
	return new CArrow(*this);
}

CArrow::CArrow()
{
	SetScale(fPoint(20.f, 20.f));
	m_fvDir = fVec2(0, 0);
	SetName(L"Missile_Player");

	CreateCollider();
	GetCollider()->SetScale(fPoint(15.f, 15.f));
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
}

void CArrow::render()
{
	fPoint pos = GetPos();
	fPoint scale = GetScale();

	fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(pos);

	CRenderManager::getInst()->RenderEllipse(
		fptRenderPos.x,
		fptRenderPos.y,
		scale.x / 2.f,
		scale.y / 2.f);

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
