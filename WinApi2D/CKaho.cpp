#include "framework.h"
#include "CKaho.h"
#include "CCollider.h"
#include "CAnimator.h"

#define GRAVITY 130
#define JUMPFORCE 100

CKaho::CKaho()
{
	m_idle = true;		//가만히 있는상태
	m_Fjump = false;	//점프 상태(공중)
	m_Djump = false;	//2단점프 상태(공중)
	m_dead = false;		//죽은 상태
	m_onfloor = true;	//바닥에 있는 상태
	m_HP = 100;			//캐릭터 체력
	
	m_velocity = 150;
	m_gravity = GRAVITY;
	m_jumpforce = JUMPFORCE;

	m_HP;
    m_pImg = CResourceManager::getInst()->LoadD2DImage(L"KahoImage", L"texture\\sKahoidle_Full.png");
    SetName(L"Kaho");
    SetScale(fPoint(70.f, 70.f));

    CreateCollider();
    GetCollider()->SetScale(fPoint(40.f, 40.f));
    GetCollider()->SetOffsetPos(fPoint(0.f, 10.f));

	//변수 이름 바꾸기
	m_pImg2 = CResourceManager::getInst()->LoadD2DImage(L"KahoWalk", L"texture\\sKahoWalk_Full.png");
	m_pImg3 = CResourceManager::getInst()->LoadD2DImage(L"KahoJump", L"texture\\sKahoJump_Full.png");
	CreateAnimator();
    //이름 속성(대상 사진) 시작위치 자를위치 자른후이동할위치 속도,애니메 갯수
	GetAnimator()->CreateAnimation(L"Kahoidle", m_pImg, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 5);
    GetAnimator()->CreateAnimation(L"RightWalk", m_pImg2, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 9);
	GetAnimator()->CreateAnimation(L"KahoJump", m_pImg3, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 2);
	GetAnimator()->Play(L"Kahoidle");
	//CRenderManager::getInst()->RenderRevFrame(m_pImg2, 0, 48, 48, 48, 0, 48, 48, 48);
	//GetAnimator()->CreateAnimation(L"LeftWalk", m_pImg2, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 9);
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
		pos.x -= m_velocity * fDT;
		if (m_onfloor)
		{
			//GetAnimator()->Play(L"LeftWalk");
		}
	}
	if (Key(VK_RIGHT))
	{
		pos.x += m_velocity * fDT;
		m_idle = false;
		if(m_onfloor)
			GetAnimator()->Play(L"RightWalk");
	}
	//점프 
	if (KeyDown(VK_UP))
	{
		--pos.y;
		m_Fjump = true;
		m_onfloor = false;
		GetAnimator()->Play(L"KahoJump");
	}

	//대기상태 (점프상태 아니고 바닥일때)
	if (false == m_Fjump&& true == m_onfloor)
	{
		GetAnimator()->Play(L"Kahoidle");
		m_gravity = 0;
		m_jumpforce = JUMPFORCE;
		//점프 
		if (KeyDown(VK_UP))
		{
			m_Fjump = true;
			m_onfloor = false;
			GetAnimator()->Play(L"KahoJump");
		}

	}
	//공중에 있을때 중력작용
	if (true == m_Fjump && false == m_onfloor)
	{
		m_gravity = GRAVITY;
		m_jumpforce -= m_gravity * fDT;
		pos.y -= m_jumpforce * fDT;
		
		if (m_jumpforce <= 0.f) //점프력이 0이되면(최고점에 올라가면)
		{
			pos.y += m_gravity * fDT;	//중력으로 떨어짐
			m_Djump = true;
		}
		
	}
	//2단점프
	//if (KeyDown(VK_UP) && true == m_Djump && false == m_onfloor)
	//{
	//	m_gravity = GRAVITY;
	//	m_jumpforce = JUMPFORCE;
	//	m_jumpforce -= m_gravity * fDT;
	//	pos.y -= m_jumpforce * fDT;

	//	if (m_jumpforce <= 0.f) //점프력이 0이되면(최고점에 올라가면)
	//	{
	//		pos.y += m_gravity * fDT;	//중력으로 떨어짐
	//	}
	//}

	if (Key(VK_DOWN))
	{
		pos.y += m_velocity * fDT;
	}
	if (Key('F'))
	{
		pos.x += 80 * fDT;
	}
	SetPos(pos);

	GetAnimator()->update();
}

void CKaho::render()
{
	component_render();
}

void CKaho::OnCollision(CCollider* pOther)
{
	/*CGameObject* pOtherObj = pOther->GetObj();
	if (pOtherObj->GetName() == L"Monster")
	{
		m_onfloor = true;
	}*/
}

void CKaho::OnCollisionEnter(CCollider* pOther)
{
	//일단 몬스터로 타일을 구현해서 점프를 구현함
	CGameObject* pOtherObj = pOther->GetObj();
	if (pOtherObj->GetName() == L"Monster")
	{
		m_onfloor = true;
		m_Fjump = false;
		m_Djump = false;
	}
}

void CKaho::OnCollisionExit(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();
	if (pOtherObj->GetName() == L"Monster")
	{
		m_onfloor = false;
	}
}
