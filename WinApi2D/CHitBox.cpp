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

	CreateCollider();
	GetCollider()->SetScale(fPoint(60.f, 50.f));
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"AttEffect", L"texture\\AttEffect.png");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"AttEffectR", m_pImg, fPoint(0.f, 0.f), fPoint(96.f, 48.f), fPoint(96.f, 0), 0.05f, 6, false);
	GetAnimator()->Play(L"AttEffectR");
}

CHitBox::~CHitBox()
{
	
}

void CHitBox::update()
{
	
	GetAnimator()->update();
}

void CHitBox::render()
{
	/*fPoint pos = GetPos();
	fPoint scale = GetScale();

	fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(pos);

	CRenderManager::getInst()->RenderEllipse(
		(fptRenderPos.x),
		(fptRenderPos.y),
		(scale.x / 2.f),
		(scale.y / 2.f));*/

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
	
	/*m_fDelay += fDT;
	if (m_fDelaytime + 0.1f <= m_fDelay)
		DeleteObj(this);*/
	
	if (nullptr != user)
	{
		//히트박스 유저위치로 방향 설정
		SetPos(user->GetPos());
		GetAnimator()->FindAnimation(L"AttEffectR")->SetFrame(0);
		
		/*if (user->GetDirect() > 0)
		{
			
			GetAnimator()->FindAnimation(L"AttEffect")->SetFrame(0);
			GetAnimator()->Play(L"AttEffect");
		}
		else
		{
			
			
			GetAnimator()->FindAnimation(L"AttEffect")->SetFrame(0);
			GetAnimator()->Play(L"AttEffect");
		}*/
	}
	
}

void CHitBox::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();
	if (pOtherObj->GetName() == L"Monster")
	{
		
	}
}
