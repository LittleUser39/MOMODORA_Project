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
	m_idle = true;		//������ �ִ»���
	m_bAttacking = false;	//���� ����
	
	m_dead = false;		//���� ����
	m_onfloor = true;	//�ٴڿ� �ִ� ����
	m_HP = 100;			//ĳ���� ü��
	
	m_velocity = 0.f;		//ó�� �ӵ�
	m_Maxvelocity = 150.f;	//�ְ�ӵ�
	m_fFriction = 50;		//����ӵ�
	m_gravity = GRAVITY;
	m_jumpforce = JUMPFORCE;
	
	//img 1= �⺻, 2 = �ȱ�, 3 = ����, 4 = ����, 5 = ����2,6 = ����3, 7 = Ȱ���(����), 8 = ������ 9 = Ȱ���(�ɾ�), 10 = �ɱ�, 11 = �극��ũ
    
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"KahoImage", L"texture\\sKahoidle_Full.png");
    SetName(L"Kaho");
    SetScale(fPoint(70.f, 70.f));
	m_cPHitbox = new CHitBox;
	m_cPHitbox->SetOwnerObj(this);
	CScene* pCurScene = CSceneManager::getInst()->GetCurScene();
	pCurScene->AddObject(m_cPHitbox, GROUP_GAMEOBJ::HITBOX_PLAYER);

	//�浹ü ���� �� �浹ü ũ��,������
    CreateCollider();
    GetCollider()->SetScale(fPoint(40.f, 55.f));
    GetCollider()->SetOffsetPos(fPoint(0.f, 13.f));
	
	//��ü �����
	CreateRigidBody();

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

void CKaho::update() //�÷��̾� ������Ʈ
{
	update_state();
	update_move();
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
		//���� ������ ������ ���� ���� �ƹ��͵� ���ѻ��°� �� ũ�� (���� �����̰� �� ũ�� ������)
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
		GetAnimator()->FindAnimation(L"KahoBow")->SetFrame(0);
	}

}

void CKaho::update_move() //�ൿ�� ���Ѱ�
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
	////���� ����(���߿� �ִ� ����)
	//if (true == m_Fjump && false == m_onfloor)
	//{
	//	m_gravity = GRAVITY;
	//	m_jumpforce -= m_gravity * fDT;
	//	pos.y -= m_jumpforce * fDT;

	//	if (m_jumpforce <= 0.f) //�������� 0�̵Ǹ�(�ְ����� �ö󰡸�)
	//	{
	//		pos.y += m_gravity * fDT;	//�߷����� ������
	//	}
	//}

	//if (KeyDown('D'))
	//{
	//	//todo Ȱ���� - ���⿡ create �̻��� �ֱ� ���� ���ݳֱ�
	//	CreateArrow();
	//	GetAnimator()->Play(L"KahoBow");
	//}

	//if (Key('F'))
	//{
	//	//todo ������ ����
	//}

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

	//ȭ�� ������Ʈ
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
	//�ϴ� ���ͷ� Ÿ���� �����ؼ� ������ ������
	CGameObject* pOtherObj = pOther->GetObj();
	if (pOtherObj->GetName() == L"Monster")
	{
		m_onfloor = true;
	}
}

void CKaho::OnCollisionExit(CCollider* pOther)
{
	//�ϴ� ���ͷ� Ÿ���� �����ؼ� ������ ������
	CGameObject* pOtherObj = pOther->GetObj();
	if (pOtherObj->GetName() == L"Monster")
	{
		m_onfloor = false;
	}
}

