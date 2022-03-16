#include "framework.h"
#include "CKaho.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CArrow.h"
#include "CHitBox.h"

#define GRAVITY 130
#define JUMPFORCE 100

CKaho::CKaho()
{
	m_idle = true;		//가만히 있는상태
	m_Fjump = false;	//점프 상태(공중)
	
	m_dead = false;		//죽은 상태
	m_onfloor = true;	//바닥에 있는 상태
	m_HP = 100;			//캐릭터 체력
	m_rolldis = false;		//캐릭터가 구르고있나
	m_rollCount = 100;		//거리
	m_velocity = 150;
	m_gravity = GRAVITY;
	m_jumpforce = JUMPFORCE;
	
	//img 1= 기본, 2 = 걷기, 3 = 점프, 4 = 공격, 5 = 공격2,6 = 공격3, 7 = 활쏘기(지상), 8 = 구르기 9 = 활쏘기(앉아)
    
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"KahoImage", L"texture\\sKahoidle_Full.png");
    SetName(L"Kaho");
    SetScale(fPoint(70.f, 70.f));

	//충돌체 생성 및 충돌체 크기,오프셋
    CreateCollider();
    GetCollider()->SetScale(fPoint(40.f, 40.f));
    GetCollider()->SetOffsetPos(fPoint(0.f, 5.f));
	
	//변수 이름 바꾸기
	m_pImg2 = CResourceManager::getInst()->LoadD2DImage(L"KahoWalk", L"texture\\sKahoWalk_Full.png");
	m_pImg3 = CResourceManager::getInst()->LoadD2DImage(L"KahoJump", L"texture\\sKahoJump_Full.png");
	m_pImg4 = CResourceManager::getInst()->LoadD2DImage(L"KahoAttack1", L"texture\\sKahoAttack_Full1.png");
	m_pImg5 = CResourceManager::getInst()->LoadD2DImage(L"KahoAttack2", L"texture\\sKahoAttack_Full2.png");
	m_pImg6 = CResourceManager::getInst()->LoadD2DImage(L"KahoAttack3", L"texture\\sKahoAttack_Full3.png");
	m_pImg7 = CResourceManager::getInst()->LoadD2DImage(L"KahoBow", L"texture\\sKahoBow_Full.png");
	m_pImg8 = CResourceManager::getInst()->LoadD2DImage(L"KahoRoll", L"texture\\sKahoRoll_Full.png");
	m_pImg9 = CResourceManager::getInst()->LoadD2DImage(L"KahoCrouchBow", L"texture\\sKahoCrouchBow_Full.png");
	CreateAnimator();
    //이름 속성(대상 사진) 시작위치 자를위치 자른후이동할위치 속도,애니메 갯수
	GetAnimator()->CreateAnimation(L"Kahoidle", m_pImg, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 5, false);
	GetAnimator()->CreateAnimation(L"KahoidleL", m_pImg, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 5, true);

	//GetAnimator()->CreateAnimation(L"RightWalk", m_pImg2, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 9); 일단 빼둠 
	GetAnimator()->CreateAnimation(L"RightWalkFull", m_pImg2, fPoint(96.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 7,false);
	GetAnimator()->CreateAnimation(L"LeftWalkFull", m_pImg2, fPoint(96.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 7, true);
	
	GetAnimator()->CreateAnimation(L"KahoJump", m_pImg3, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 2, false);
	GetAnimator()->CreateAnimation(L"KahoAttack1", m_pImg4, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 6, false);
	GetAnimator()->CreateAnimation(L"KahoAttack2", m_pImg5, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 6, false);
	GetAnimator()->CreateAnimation(L"KahoAttack3", m_pImg6, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 6, false);
	GetAnimator()->CreateAnimation(L"KahoBow", m_pImg7, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.2f, 5, false);
	GetAnimator()->CreateAnimation(L"KahoRoll",m_pImg8,fPoint(0.f,0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.2f, 7, false);
	GetAnimator()->CreateAnimation(L"KahoCrouchBow", m_pImg9, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.2f, 5, false);

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
	//바닥일때 좌우 애니메
	if(KeyUp(VK_RIGHT)&& m_onfloor)
		GetAnimator()->Play(L"Kahoidle");
	if (KeyUp(VK_LEFT)&& m_onfloor)
		GetAnimator()->Play(L"KahoidleL");

	if (Key(VK_LEFT))
	{
		pos.x -= m_velocity * fDT;
		if (m_onfloor)
		{
			GetAnimator()->Play(L"LeftWalkFull");
		}
	}

	if (Key(VK_RIGHT))
	{
		pos.x += m_velocity * fDT;
		if (m_onfloor)
		{
			GetAnimator()->Play(L"RightWalkFull");
		}
	}

	if (Key(VK_DOWN))
	{
		//todo 앉기랑 사다리 있으면 사다리 내려가기
		//pos.y += m_velocity * fDT;
	}

	if (Key(VK_UP))
	{
		//todo 사다리있으면 사다리 오르기
	}

	//딜레이 구현
	delay += fDT;
	
	//연속 공격이 아닐때 콤보0으로 
	if (!IsComboAttck())
		combo = 0;
	//공격 구현 여기다가 히트박스(충돌체) 구현
	if (CanAttack())
	{
		if (KeyDown('A'))
		{
			//콤보가 없을때 1번째 공격
			if (0 == combo)
			{
				Attack();
				CreateHitBox();
				GetAnimator()->Play(L"KahoAttack1");
			}
			//콤보가 1일때 2번째 공격
			else if (IsComboAttck()&& combo == 1)
			{
				ComboAttack2();
				GetAnimator()->Play(L"KahoAttack2");
			}
			//콤보가 2일때 3번째 공격
			else if (IsComboAttck() &&combo == 2)
			{
				ComboAttack3();
				GetAnimator()->Play(L"KahoAttack3");
			}
		}
	}

	if (KeyDown('S'))
	{
		//todo 활공격 - 여기에 create 미사일 넣기 충전 공격넣기
		CreateArrow();
		GetAnimator()->Play(L"KahoBow");
	}
	if (Key(VK_DOWN) && Key('S'))
		GetAnimator()->Play(L"KahoCrouchBow");
	//구르기
	if (Key('F') && false == m_rolldis)
	{
		//todo 구르기 - 좌우로 조금 이동 하면서 플레이어는 무적
		pos.x += m_velocity * DT;
		
		if (pos.x > pos.x + m_rollCount)
			m_rolldis = true;
		GetAnimator()->Play(L"KahoRoll");
		
	}
	 
	//점프 하는 상태
	if (KeyDown('D'))
	{
		m_gravity = GRAVITY;
		m_jumpforce = JUMPFORCE;
		m_Fjump = true;
		m_onfloor = false;
		GetAnimator()->Play(L"KahoJump"); 
	}
	//점프 상태(공중에 있는 상태)
	if (true == m_Fjump && false == m_onfloor)
	{
		m_gravity = GRAVITY;
		m_jumpforce -= m_gravity * fDT;
		pos.y -= m_jumpforce * fDT;

		if (m_jumpforce <= 0.f) //점프력이 0이되면(최고점에 올라가면)
		{
			pos.y += m_gravity * fDT;	//중력으로 떨어짐
		}
	}
	
	SetPos(pos);

	GetAnimator()->update();
}

void CKaho::render()
{
	component_render();
}

void CKaho::CreateArrow()
{
	fPoint fpArrowpos = GetPos();
	fpArrowpos.x += GetScale().x / 2.f;

	//화살 오브젝트
	CArrow* pArrow = new CArrow;
	pArrow->SetPos(fpArrowpos);
	pArrow->SetDir(fVec2(1, 0));

	CreateObj(pArrow, GROUP_GAMEOBJ::MISSILE_PLAYER);
}

void CKaho::CreateHitBox()
{
	fPoint fpHitBoxPos = GetPos();
	fpHitBoxPos.x += GetScale().x / 2.f;

	// 히트박스 오브젝트
	CHitBox* pHitBox = new CHitBox;
	pHitBox->SetPos(fpHitBoxPos);
	pHitBox->SetDir(fVec2(1, 0));

	CreateObj(pHitBox, GROUP_GAMEOBJ::HITBOX_PLAYER);
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
	}
}

void CKaho::OnCollisionExit(CCollider* pOther)
{
	//일단 몬스터로 타일을 구현해서 점프를 구현함
	CGameObject* pOtherObj = pOther->GetObj();
	if (pOtherObj->GetName() == L"Monster")
	{
		m_onfloor = false;
	}
}

bool CKaho::CanAttack()
{
	return fdealy < delay;
}
bool CKaho::Attack()
{
	delay = 0;
	combo++;
	return fdealy < delay;
}
bool CKaho::ComboAttack2()
{
	delay = 0;
	combo++;
	return fdealy < delay;
}
bool CKaho::ComboAttack3()
{
	delay = 0;
	combo = 0;
	return fdealy < delay;
}

bool CKaho::IsComboAttck()
{
	return fcombo > delay;
}