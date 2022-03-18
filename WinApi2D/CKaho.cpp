#include "framework.h"
#include "CKaho.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"
#include "CArrow.h"
#include "CHitBox.h"
#include "CScene.h"

#define GRAVITY 130
#define JUMPFORCE 100

CKaho::CKaho() : m_eCurState(PLAYER_STATE::IDLE)
				, m_ePreState(PLAYER_STATE::WALK)
				, m_iCurDir(1)
				, m_iPreDir(1)
{
	m_idle = true;		//가만히 있는상태
	m_bAttacking = false;	//공격 상태
	
	m_dead = false;		//죽은 상태
	m_onfloor = true;	//바닥에 있는 상태
	m_HP = 100;			//캐릭터 체력
	
	m_velocity = 0.f;		//처음 속도
	m_Maxvelocity = 150.f;	//최고속도
	m_fFriction = 50;		//멈출속도
	m_gravity = GRAVITY;
	m_jumpforce = JUMPFORCE;
	
	//img 1= 기본, 2 = 걷기, 3 = 점프, 4 = 공격, 5 = 공격2,6 = 공격3, 7 = 활쏘기(지상), 8 = 구르기 9 = 활쏘기(앉아), 10 = 앉기, 11 = 브레이크
    
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"KahoImage", L"texture\\sKahoidle_Full.png");
    SetName(L"Kaho");
    SetScale(fPoint(70.f, 70.f));
	m_cPHitbox = new CHitBox;
	m_cPHitbox->SetOwnerObj(this);
	CScene* pCurScene = CSceneManager::getInst()->GetCurScene();
	pCurScene->AddObject(m_cPHitbox, GROUP_GAMEOBJ::HITBOX_PLAYER);

	//충돌체 생성 및 충돌체 크기,오프셋
    CreateCollider();
    GetCollider()->SetScale(fPoint(40.f, 55.f));
    GetCollider()->SetOffsetPos(fPoint(0.f, 13.f));
	
	//강체 만들기
	CreateRigidBody();

	//변수 이름 바꾸기
	m_pImg2 = CResourceManager::getInst()->LoadD2DImage(L"KahoWalk", L"texture\\sKahoWalk_Full.png");
	m_pImg3 = CResourceManager::getInst()->LoadD2DImage(L"KahoJump", L"texture\\sKahoJump_Full.png");
	m_pImg4 = CResourceManager::getInst()->LoadD2DImage(L"KahoAttack1", L"texture\\sKahoAttack_Full1.png");
	m_pImg5 = CResourceManager::getInst()->LoadD2DImage(L"KahoAttack2", L"texture\\sKahoAttack_Full2.png");
	m_pImg6 = CResourceManager::getInst()->LoadD2DImage(L"KahoAttack3", L"texture\\sKahoAttack_Full3.png");
	m_pImg7 = CResourceManager::getInst()->LoadD2DImage(L"KahoBow", L"texture\\sKahoBow_Full.png");
	m_pImg8 = CResourceManager::getInst()->LoadD2DImage(L"KahoRoll", L"texture\\sKahoRoll_Full.png");
	m_pImg9 = CResourceManager::getInst()->LoadD2DImage(L"KahoCrouchBow", L"texture\\sKahoCrouchBow_Full.png");
	m_pImg10 = CResourceManager::getInst()->LoadD2DImage(L"KahoCrouch", L"texture\\sKahoCrouch_Full.png");
	m_pImg11 = CResourceManager::getInst()->LoadD2DImage(L"KahoBrake", L"texture\\sKahoBrake_Full.png");
	
	CreateAnimator();
    //이름 속성(대상 사진) 시작위치 자를위치 자른후이동할위치 속도,애니메 갯수
	GetAnimator()->CreateAnimation(L"KahoidleR", m_pImg, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 5, true);
	GetAnimator()->CreateAnimation(L"KahoidleL", m_pImg, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 5, true, true);

	//GetAnimator()->CreateAnimation(L"RightWalk", m_pImg2, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 9); 일단 빼둠 
	GetAnimator()->CreateAnimation(L"RightWalkFull", m_pImg2, fPoint(96.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 7,true);
	GetAnimator()->CreateAnimation(L"LeftWalkFull", m_pImg2, fPoint(96.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 7, true, true);
	
	GetAnimator()->CreateAnimation(L"KahoJump", m_pImg3, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 2, false);
	
	GetAnimator()->CreateAnimation(L"KahoAttack1R", m_pImg4, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 6, false);
	GetAnimator()->CreateAnimation(L"KahoAttack1L", m_pImg4, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 6, false, true);

	GetAnimator()->CreateAnimation(L"KahoAttack2R", m_pImg5, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 6, false);
	GetAnimator()->CreateAnimation(L"KahoAttack2L", m_pImg5, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 6, false, true);

	GetAnimator()->CreateAnimation(L"KahoAttack3R", m_pImg6, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 6, false);
	GetAnimator()->CreateAnimation(L"KahoAttack3L", m_pImg6, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 6, false, true);

	GetAnimator()->CreateAnimation(L"KahoBow", m_pImg7, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.2f, 5, false);
	GetAnimator()->CreateAnimation(L"KahoRoll",m_pImg8,fPoint(0.f,0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.2f, 7, false);
	GetAnimator()->CreateAnimation(L"KahoCrouchBow", m_pImg9, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.2f, 5, false);
	GetAnimator()->CreateAnimation(L"KahoCrouch", m_pImg10, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.2f, 3, false);

	GetAnimator()->CreateAnimation(L"KahoBrake", m_pImg11, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.2f, 6, false);

	
	
}

CKaho::~CKaho()
{
}

CKaho* CKaho::Clone()
{
    return nullptr;
}

void CKaho::update() //플레이어 업데이트
{
	update_state();
	update_move();
	update_animation();

	
	//if (Key(VK_DOWN))
	//{
	//	//todo 앉기랑 사다리 있으면 사다리 내려가기
	//	//pos.y += m_velocity * fDT;
	//	if (m_onfloor)
	//	{
	//		GetAnimator()->Play(L"KahoCrouch");
	//	}
	//}

	//if (Key(VK_UP))
	//{
	//	//todo 사다리있으면 사다리 오르기
	//}
	

	//if (Key(VK_DOWN) && Key('S'))
	//	GetAnimator()->Play(L"KahoCrouchBow");
	//
	
	//점프 하는 상태
	
	GetAnimator()->update();
	m_ePreState = m_eCurState;
	m_iPreDir = m_iCurDir;
}

void CKaho::update_state() //현재 상태에 관한거
{
	m_fDelay += fDT;

	//속도가 없을때 대기상태로 만들어야함 그래서 속도를 가져옴
	if (0.f == GetRigidBody()->GetSpeed())
	{
		//내가 설정한 딜레이 보다 내가 아무것도 안한상태가 더 크면 (나의 딜레이가 더 크면 대기상태)
		if (m_fDelaytime + 0.2f <= m_fDelay)
		{
			m_bAttacking = false;
			m_eCurState = PLAYER_STATE::IDLE;
		}
	}

	if (KeyDown(VK_LEFT)&& !m_bAttacking )
	{
		m_iCurDir = -1;
		m_eCurState = PLAYER_STATE::WALK;
	}

	if (KeyDown(VK_RIGHT) && !m_bAttacking )
	{
		m_iCurDir = 1;
		m_eCurState = PLAYER_STATE::WALK;
	}
	if (KeyUp(VK_RIGHT))
	{
		m_eCurState = PLAYER_STATE::BRAKE;
		GetAnimator()->FindAnimation(L"KahoBrake")->SetFrame(0);
	}
	
	if (KeyDown('A'))
	{
		//공격상태
		m_bAttacking = true;
		//딜레이 타임보다 늦게 누르면 콤보  없애줌
		if (m_fDelaytime + 0.1f <= m_fDelay)
			m_iCombo = 0;
		//콤보3이거나 같으면 다시 0으로 바꿔줌
		if (m_iCombo >= 3)
			m_iCombo = 0;
		m_iCombo++;
		
		if (m_iCombo == 1)
		{
			m_fDelay = 0;
			m_eCurState = PLAYER_STATE::ATTACK1;
			GetAnimator()->FindAnimation(L"KahoAttack1R")->SetFrame(0);
			GetAnimator()->FindAnimation(L"KahoAttack1L")->SetFrame(0);

			m_cPHitbox->create();
		}
		//콤보가 2일때 3번째 공격
		if ( m_iCombo == 2)
		{
			m_fDelay = 0;
			m_eCurState = PLAYER_STATE::ATTACK2;
			GetAnimator()->FindAnimation(L"KahoAttack2R")->SetFrame(0);
			GetAnimator()->FindAnimation(L"KahoAttack2L")->SetFrame(0);

			m_cPHitbox->create();
		}

		//콤보가 2일때 3번째 공격
		else if ( m_iCombo == 3)
		{
			m_fDelay = 0;
			m_eCurState = PLAYER_STATE::ATTACK3;
			
			GetAnimator()->FindAnimation(L"KahoAttack3R")->SetFrame(0);
			GetAnimator()->FindAnimation(L"KahoAttack3L")->SetFrame(0);
			
			m_cPHitbox->create();
		}
	}
	if (KeyDown('D'))
	{
		//todo 활공격 - 행동 넣어야함
		GetAnimator()->FindAnimation(L"KahoBow")->SetFrame(0);
	}

}

void CKaho::update_move() //행동에 관한거
{
	CRigidBody* pRigid = GetRigidBody();

	if (Key(VK_LEFT) && !m_bAttacking)
	{
		pRigid->AddForce(fPoint(-200.f, 0.f));
	}

	if (KeyDown(VK_LEFT) && !m_bAttacking)
	{
		pRigid->AddVelocity(fPoint(-200.f, 0.f));
	}

	if (Key(VK_RIGHT) && !m_bAttacking)
	{
		pRigid->AddForce(fPoint(200.f, 0.f));
	}
	if (KeyDown(VK_RIGHT) && !m_bAttacking)
	{
		pRigid->AddVelocity(fPoint(200.f, 0.f));
	}

	

	//if (KeyDown('S'))
	//{
	//	m_gravity = GRAVITY;
	//	m_jumpforce = JUMPFORCE;
	//	m_Fjump = true;
	//	m_onfloor = false;
	//	GetAnimator()->Play(L"KahoJump");
	//}
	////점프 상태(공중에 있는 상태)
	//if (true == m_Fjump && false == m_onfloor)
	//{
	//	m_gravity = GRAVITY;
	//	m_jumpforce -= m_gravity * fDT;
	//	pos.y -= m_jumpforce * fDT;

	//	if (m_jumpforce <= 0.f) //점프력이 0이되면(최고점에 올라가면)
	//	{
	//		pos.y += m_gravity * fDT;	//중력으로 떨어짐
	//	}
	//}

	//if (KeyDown('D'))
	//{
	//	//todo 활공격 - 여기에 create 미사일 넣기 충전 공격넣기
	//	CreateArrow();
	//	GetAnimator()->Play(L"KahoBow");
	//}

	//if (Key('F'))
	//{
	//	//todo 구르기 구현
	//}

}

void CKaho::update_animation()	//애니메이션에 관한거 - 상태에 따른 애니메이션 출력
{
	if (m_ePreState == m_eCurState && m_iCurDir == m_iPreDir)
	{
		return;
	}

	switch (m_eCurState)
	{
	case PLAYER_STATE::IDLE:
	{	if (-1 == m_iCurDir && m_onfloor)
	{
		GetAnimator()->Play(L"KahoidleL");
	}
		else if (1 == m_iCurDir && m_onfloor)
	{
		GetAnimator()->Play(L"KahoidleR");
	}
	}
	break;

	case PLAYER_STATE::WALK:
	{
		if (-1 == m_iCurDir && m_onfloor)
		{
			GetAnimator()->Play(L"LeftWalkFull");
		}
		else if (1 == m_iCurDir && m_onfloor)
		{
			GetAnimator()->Play(L"RightWalkFull");
		}
	}
	break;

	case PLAYER_STATE::ATTACK1:
	{
		if (-1 == m_iCurDir && m_onfloor)
		{
			GetAnimator()->Play(L"KahoAttack1L");
		}
		else if (1 == m_iCurDir && m_onfloor)
		{
			GetAnimator()->Play(L"KahoAttack1R");
		}
	}
	break;
	case PLAYER_STATE::ATTACK2:
	{
		if (-1 == m_iCurDir && m_onfloor)
		{
			GetAnimator()->Play(L"KahoAttack2L");
		}
		else if (1 == m_iCurDir && m_onfloor)
		{
			GetAnimator()->Play(L"KahoAttack2R");
		}
	}
	break;
	case PLAYER_STATE::ATTACK3:
	{
		if (-1 == m_iCurDir && m_onfloor)
		{
			GetAnimator()->Play(L"KahoAttack3L");
		}
		else if (1 == m_iCurDir && m_onfloor)
		{
			GetAnimator()->Play(L"KahoAttack3R");
		}
	}
	break;
	case PLAYER_STATE::BRAKE:
	{
		GetAnimator()->Play(L"KahoBrake");
	}
	break;
	case PLAYER_STATE::DEAD:
	{}
	break;

	}
}

void CKaho::render()
{
	component_render();
}

float CKaho::GetDirect()
{
	return m_iCurDir;
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

