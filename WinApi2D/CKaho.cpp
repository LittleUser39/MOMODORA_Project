#include "framework.h"
#include "CKaho.h"
#include "CCollider.h"
#include "CAnimator.h"
CKaho::CKaho()
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(L"KahoImage", L"texture\\sKahoidle_Full.png");
    SetName(L"Kaho");
    SetScale(fPoint(70.f, 70.f));

    CreateCollider();
    GetCollider()->SetScale(fPoint(40.f, 40.f));
    GetCollider()->SetOffsetPos(fPoint(0.f, 10.f));

	m_pImg2 = CResourceManager::getInst()->LoadD2DImage(L"KahoWalk", L"texture\\sKahoWalk_Full.png");
    CreateAnimator();
    //이름 속성(대상 사진) 시작위치 자를위치 자른후이동할위치 속도,애니메 갯수
	GetAnimator()->CreateAnimation(L"Kahoidle", m_pImg, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 5);
    GetAnimator()->CreateAnimation(L"RightWalk", m_pImg2, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 9);
	GetAnimator()->Play(L"Kahoidle");
}

CKaho::~CKaho()
{
}

CKaho* CKaho::Clone()
{
    return nullptr;
}

void CKaho::update()
{
	fPoint pos = GetPos();

	if (Key(VK_LEFT))
	{
		pos.x -= m_fVelocity * fDT;
		
	}
	if (KeyDown(VK_RIGHT))
	{
		pos.x += m_fVelocity * fDT;
		GetAnimator()->Play(L"RightWalk");
	}
	if (Key(VK_UP))
	{
		pos.y -= m_fVelocity * fDT;
	}
	if (Key(VK_DOWN))
	{
		pos.y += m_fVelocity * fDT;
	}

	SetPos(pos);

	GetAnimator()->update();
}

void CKaho::render()
{
	component_render();
}
