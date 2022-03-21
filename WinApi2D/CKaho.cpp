#include "framework.h"
#include "CKaho.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"
#include "CArrow.h"
#include "CHitBox.h"
#include "CScene.h"
#include "CGravity.h"

CKaho* CKaho::instance = nullptr;

CKaho::CKaho() : m_eCurState(PLAYER_STATE::IDLE)
				, m_ePreState(PLAYER_STATE::WALK)
				, m_iCurDir(1)
				, m_iPreDir(1)
{
	
	m_bAttacking = false;	//���� ����
	m_bDead = false;		//���� ����
	m_onfloor = true;	//�ٴڿ� �ִ� ����
	m_bJump = false;
	
	
	
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"KahoImage", L"texture\\sKahoidle_Full.png");
    SetName(L"Kaho");
    SetScale(fPoint(70.f, 70.f));
	m_cPHitbox = new CHitBox;
	m_cPHitbox->SetOwnerObj(this);
	m_cPHitbox->SetName(L"Player_hitbox");
	CScene* pCurScene = CSceneManager::getInst()->GetCurScene();
	pCurScene->AddObject(m_cPHitbox, GROUP_GAMEOBJ::HITBOX_PLAYER);

	//�浹ü ���� �� �浹ü ũ��,������
    CreateCollider();
    GetCollider()->SetScale(fPoint(40.f, 55.f));
    GetCollider()->SetOffsetPos(fPoint(0.f, 13.f));
	
	//img 1= �⺻, 2 = �ȱ�, 3 = ����, 4 = ����, 5 = ����2,6 = ����3, 7 = Ȱ���(����), 8 = ������ 9 = Ȱ���(�ɾ�), 10 = �ɱ�, 11 = �극��ũ

	//���� �̸� �ٲٱ�
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
    //�̸� �Ӽ�(��� ����) ������ġ �ڸ���ġ �ڸ����̵�����ġ �ӵ�,�ִϸ� ����
	GetAnimator()->CreateAnimation(L"KahoidleR", m_pImg, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 5, true);
	GetAnimator()->CreateAnimation(L"KahoidleL", m_pImg, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 5, true, true);

	//GetAnimator()->CreateAnimation(L"RightWalk", m_pImg2, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 9); �ϴ� ���� 
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

	GetAnimator()->CreateAnimation(L"KahoRollR",m_pImg8,fPoint(0.f,0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.2f, 7, false);
	GetAnimator()->CreateAnimation(L"KahoRollL", m_pImg8, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.2f, 7, false, true);

	GetAnimator()->CreateAnimation(L"KahoCrouchBow", m_pImg9, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.2f, 5, false);
	GetAnimator()->CreateAnimation(L"KahoCrouch", m_pImg10, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.2f, 3, false);

	GetAnimator()->CreateAnimation(L"KahoBrakeR", m_pImg11, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.2f, 6, false);
	GetAnimator()->CreateAnimation(L"KahoBrakeL", m_pImg11, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.2f, 6, false, true);


	
	//��ü �����
	CreateRigidBody();
	//�߷� ����
	CreateGravity();
}

CKaho::~CKaho()
{
	instance = nullptr;
}

CKaho* CKaho::Clone()
{
    return nullptr;
}

void CKaho::update() //�÷��̾� ������Ʈ
{
	update_move();
	update_state();
	update_animation();
	
	//if (Key(VK_DOWN))
	//{
	//	//todo �ɱ�� ��ٸ� ������ ��ٸ� ��������
	//	//pos.y += m_velocity * fDT;
	//	if (m_onfloor)
	//	{
	//		GetAnimator()->Play(L"KahoCrouch");
	//	}
	//}

	//if (Key(VK_UP))
	//{
	//	//todo ��ٸ������� ��ٸ� ������
	//}
	

	//if (Key(VK_DOWN) && Key('S'))
	//	GetAnimator()->Play(L"KahoCrouchBow");
	//
	
	//���� �ϴ� ����
	
	GetAnimator()->update();
	m_ePreState = m_eCurState;
	m_iPreDir = m_iCurDir;
}

void CKaho::update_state() //���� ���¿� ���Ѱ�
{
	m_fDelay += fDT;

	//�ӵ��� ������ �����·� �������� �׷��� �ӵ��� ������
	if (0.f == GetRigidBody()->GetSpeed())
	{
		if (m_fDelaytime + 0.05f <= m_fDelay && m_bAttacking)
			//���� ������ ������ ���� ���� �ƹ��͵� ���ѻ��°� �� ũ�� (���� �����̰� �� ũ�� ������)
		{
			m_bAttacking = false;
			m_eCurState = PLAYER_STATE::IDLE;
		}
		
	}

	if (KeyDown(VK_LEFT)&& !m_bAttacking )
	{
		m_iCurDir = -1;
		if (PLAYER_STATE::JUMP != m_eCurState)
			m_eCurState = PLAYER_STATE::WALK;
	}

	if (KeyDown(VK_RIGHT) && !m_bAttacking )
	{
		m_iCurDir = 1;
		if (PLAYER_STATE::JUMP != m_eCurState)
			m_eCurState = PLAYER_STATE::WALK;
	}

	if (KeyUp(VK_RIGHT)&&m_iCurDir==1)
	{
		m_eCurState = PLAYER_STATE::BRAKE;
		GetAnimator()->FindAnimation(L"KahoBrakeR")->SetFrame(0);
	}

	if (KeyUp(VK_LEFT) && m_iCurDir == -1)
	{
		m_eCurState = PLAYER_STATE::BRAKE;
		GetAnimator()->FindAnimation(L"KahoBrakeL")->SetFrame(0);
	}

	if (m_eCurState == PLAYER_STATE::BRAKE && 0.f == GetRigidBody()->GetSpeed())
	{
		m_eCurState = PLAYER_STATE::IDLE;
	}

	if (KeyDown('S')&& !m_bJump)
	{
		m_eCurState = PLAYER_STATE::JUMP;
		if (GetRigidBody()&&!m_bJump)
		{
			m_bJump = true;
		}
	}
	
	if (KeyDown('A'))
	{
		//���ݻ���
		m_bAttacking = true;
		//������ Ÿ�Ӻ��� �ʰ� ������ �޺�  ������
		if (m_fDelaytime + 0.1f <= m_fDelay)
			m_iCombo = 0;
		//�޺�3�̰ų� ������ �ٽ� 0���� �ٲ���
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
		//�޺��� 2�϶� 3��° ����
		if ( m_iCombo == 2)
		{
			m_fDelay = 0;
			m_eCurState = PLAYER_STATE::ATTACK2;
			GetAnimator()->FindAnimation(L"KahoAttack2R")->SetFrame(0);
			GetAnimator()->FindAnimation(L"KahoAttack2L")->SetFrame(0);

			m_cPHitbox->create();
		}

		//�޺��� 2�϶� 3��° ����
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
		//todo Ȱ���� - �ൿ �־����
		CreateArrow();
		m_eCurState = PLAYER_STATE::BOW;
		GetAnimator()->FindAnimation(L"KahoBow")->SetFrame(0);
	}
	if (KeyDown('F'))
	{
		m_eCurState = PLAYER_STATE::ROLL;
		if (m_iCurDir == 1)
			GetAnimator()->FindAnimation(L"KahoRollR")->SetFrame(0);
		else if(m_iCurDir == -1)
			GetAnimator()->FindAnimation(L"KahoRollL")->SetFrame(0);
	}
}

void CKaho::update_move() //�ൿ�� ���Ѱ�
{
	CRigidBody* pRigid = GetRigidBody();
	fPoint pos = GetPos();
	// ���Ⱑ ���� �ִ°Ű�

	if (Key(VK_LEFT) && !m_bAttacking)
	{
		pRigid->AddForce(fPoint(-300.f, 0.f));
	}
	if (Key(VK_RIGHT) && !m_bAttacking)
	{
		pRigid->AddForce(fPoint(300.f, 0.f));
	}
	//�ű⿡ �ӵ��� ��
	if (KeyDown(VK_LEFT))
	{
		pRigid->SetVelocity(fPoint(-100.f, pRigid->GetVelocity().y));
	}
	if (KeyDown(VK_RIGHT))
	{
		pRigid->SetVelocity(fPoint(100.f, pRigid->GetVelocity().y));
	}
	// todo �ɱ� Ű�� �ٲ����
	if (Key(VK_DOWN) && !m_bAttacking)
	{
			
	}
	if (KeyDown(VK_DOWN) && !m_bAttacking)
	{
		
	}
	if (KeyDown('A'))
	{
		if (m_iCurDir == 1)
		{
			pRigid->SetVelocity(fPoint(30.f, pRigid->GetVelocity().y));
		}
		else if (m_iCurDir == -1)
		{
			pRigid->SetVelocity(fPoint(-30.f, pRigid->GetVelocity().y));
		}
	}
	//����
	if (KeyDown('S') && !m_bJump)
	{
		GetRigidBody()->SetVelocity(fVec2(GetRigidBody()->GetVelocity().x, -300.f));
	}

	if (KeyDown('F'))
	{
		if (m_iCurDir == 1)
		{
			GetRigidBody()->SetVelocity(fVec2(300.f, GetRigidBody()->GetVelocity().y));
		}
		else if (m_iCurDir == -1)
		{
			GetRigidBody()->SetVelocity(fVec2(-300.f, GetRigidBody()->GetVelocity().y));
		}
	}
	
	

}

void CKaho::update_animation()	//�ִϸ��̼ǿ� ���Ѱ� - ���¿� ���� �ִϸ��̼� ���
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
	case PLAYER_STATE::BOW:
	{
		GetAnimator()->Play(L"KahoBow");
	}
	break;
	case PLAYER_STATE::BRAKE:
	{
		if (-1 == m_iCurDir && m_onfloor) 
		{
			GetAnimator()->Play(L"KahoBrakeL");
		}
		else if (1 == m_iCurDir && m_onfloor)
		{
			GetAnimator()->Play(L"KahoBrakeR");
		}
	}
	break;
	
	case PLAYER_STATE::ROLL:
	{
		if (1 == m_iCurDir)
			GetAnimator()->Play(L"KahoRollR");
		else if (-1 == m_iCurDir)
			GetAnimator()->Play(L"KahoRollL");

	}
	break;
	
	case PLAYER_STATE::DEAD:
	{}
	break;

	}
}

void CKaho::update_CollTime()
{
	if (!m_bCanRoll)
	{
		m_fRollTime = DT;
		if (m_fRollTime >= m_fRollCoolTime)
			m_bCanRoll = true;
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

	//ȭ�� ������Ʈ
	CArrow* pArrow = new CArrow;
	pArrow->SetPos(fpArrowpos);
	pArrow->SetDir(fVec2(1, 0));

	CreateObj(pArrow, GROUP_GAMEOBJ::MISSILE_PLAYER);
}

void CKaho::OnCollision(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();
	if (L"tile" == pOtherObj->GetName())
	{
		 m_bJump = false;
	}
}

void CKaho::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();
	if (L"tile" == pOtherObj->GetName())
	{
		/*fPoint vPos = GetPos();
		if (vPos.y < pOtherObj->GetPos().y)
		{
			m_eCurState = PLAYER_STATE::IDLE;
		}*/
	}
}

void CKaho::OnCollisionExit(CCollider* pOther)
{
	
}

void CKaho::RegisterPlayer()
{
	instance = this;
}

CKaho* CKaho::GetPlayer()
{
	return instance;
}

