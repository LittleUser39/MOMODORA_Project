#include "framework.h"
#include "CDagger.h"
#include "CAnimator.h"
#include "CCollider.h"

CDagger::CDagger()
{
	SetScale(fPoint(16.f, 16.f));
	m_fvDir = fVec2(0, 0);
	SetName(L"Imp_Dagger");

	CreateCollider();
	GetCollider()->SetScale(fPoint(16.f, 16.f));

	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"ImpDagger", L"texture\\sDagger.png");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"ImpDaggerL", m_pImg, fPoint(0,0), fPoint(16.f,16.f), fPoint(0,0), 0.1f, 1, true, false);
	GetAnimator()->CreateAnimation(L"ImpDaggerR", m_pImg, fPoint(0,0), fPoint(16.f, 16.f), fPoint(0, 0), 0.1f, 1, true, true);
	
}

CDagger::~CDagger()
{

}

CDagger* CDagger::Clone()
{
	return nullptr;
}

void CDagger::update()
{
	fPoint pos = GetPos();

	pos.x += m_fVelocity * m_fvDir.x * fDT;
	pos.y += m_fVelocity * m_fvDir.y * fDT;

	SetPos(pos);

	GetAnimator()->update();
}

void CDagger::render()
{
	component_render();
}

void CDagger::SetDir(fVec2 vec)
{
	m_fvDir = vec.normalize();
}

void CDagger::SetDir(float theta)
{
	m_fvDir.x = (float)cos(theta);
	m_fvDir.y = (float)sin(theta);
}

void CDagger::OnCollisionEnter(CCollider* pOther)
{
}
