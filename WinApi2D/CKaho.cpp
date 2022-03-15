#include "framework.h"
#include "CKaho.h"
#include "CCollider.h"
#include "CAnimator.h"

#define GRAVITY 130
#define JUMPFORCE 100

CKaho::CKaho()
{
	m_idle = true;		//������ �ִ»���
	m_Fjump = false;	//���� ����(����)
	m_Djump = false;	//2������ ����(����)
	m_dead = false;		//���� ����
	m_onfloor = true;	//�ٴڿ� �ִ� ����
	m_HP = 100;			//ĳ���� ü��
	m_rolldis = false;		//ĳ���Ͱ� �������ֳ�
	m_rollCount = 100;		//�Ÿ�
	m_AttackCount = 0;
	m_velocity = 150;
	m_gravity = GRAVITY;
	m_jumpforce = JUMPFORCE;

	//img 1= �⺻, 2 = �ȱ�, 3 = ����, 4 = ����, 5 = ����2,6 = ����3, 7 = Ȱ���(����), 8 = ������
    m_pImg = CResourceManager::getInst()->LoadD2DImage(L"KahoImage", L"texture\\sKahoidle_Full.png");
    SetName(L"Kaho");
    SetScale(fPoint(70.f, 70.f));

    CreateCollider();
    GetCollider()->SetScale(fPoint(40.f, 40.f));
    GetCollider()->SetOffsetPos(fPoint(0.f, 10.f));

	//���� �̸� �ٲٱ�
	m_pImg2 = CResourceManager::getInst()->LoadD2DImage(L"KahoWalk", L"texture\\sKahoWalk_Full.png");
	m_pImg3 = CResourceManager::getInst()->LoadD2DImage(L"KahoJump", L"texture\\sKahoJump_Full.png");
	m_pImg4 = CResourceManager::getInst()->LoadD2DImage(L"KahoAttack1", L"texture\\sKahoAttack_Full1.png");
	m_pImg5 = CResourceManager::getInst()->LoadD2DImage(L"KahoAttack2", L"texture\\sKahoAttack_Full2.png");
	m_pImg7 = CResourceManager::getInst()->LoadD2DImage(L"KahoBow", L"texture\\sKahoBow_Full.png");
	m_pImg8 = CResourceManager::getInst()->LoadD2DImage(L"KahoRoll", L"texture\\sKahoRoll_Full.png");
	CreateAnimator();
    //�̸� �Ӽ�(��� ����) ������ġ �ڸ���ġ �ڸ����̵�����ġ �ӵ�,�ִϸ� ����
	GetAnimator()->CreateAnimation(L"Kahoidle", m_pImg, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 5);
    //GetAnimator()->CreateAnimation(L"RightWalk", m_pImg2, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 9); �ϴ� ���� 
	GetAnimator()->CreateAnimation(L"RightWalkFull", m_pImg2, fPoint(96.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 7);
	GetAnimator()->CreateAnimation(L"KahoJump", m_pImg3, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 2);
	GetAnimator()->CreateAnimation(L"KahoAttack1", m_pImg4, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"KahoAttack2", m_pImg5, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"KahoBow", m_pImg7, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.2f, 5);
	GetAnimator()->CreateAnimation(L"KahoRoll",m_pImg8,fPoint(0.f,0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.2f, 7);
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
	if(KeyUp(VK_RIGHT))
		GetAnimator()->Play(L"Kahoidle");
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
		if (m_onfloor)
		{
			GetAnimator()->Play(L"RightWalkFull");
		}
	}

	if (Key(VK_DOWN))
	{
		//todo �ɱ�� ��ٸ� ������ ��ٸ� ��������
		pos.y += m_velocity * fDT;
	}

	if (Key(VK_UP))
	{
		//todo ��ٸ������� ��ٸ� ������
	}

	if (KeyDown('A')&& 0 == m_AttackCount)
	{
		//todo ���� - ���⿡ �浹ü ���� �������� ��������
		GetAnimator()->Play(L"KahoAttack1");
		m_AttackCount++;
		
	}
	if (KeyUp('A'))
		m_AttackCount--;
	/*if (Key('A') && 1 == m_AttackCount)
	{
		GetAnimator()->Play(L"KahoAttack2");
		m_AttackCount--;
	}*/
	
	if (KeyDown('S'))
	{
		//todo Ȱ���� - ���⿡ create �̻��� �ֱ� ���� ���ݳֱ�
		GetAnimator()->Play(L"KahoBow");
	}

	//������
	//if (false == m_rolldis)
	//{
	//	//todo ������ - �¿�� ���� �̵� �ϸ鼭 �÷��̾�� ����
	//	pos.x += m_velocity * DT;
	//	if (pos.x > pos.x + m_rollCount)
	//		m_rolldis = true;
	//	GetAnimator()->Play(L"KahoRoll");
	//	
	//}
	// 
	//������ (�������� �ƴϰ� �ٴ��϶�)
//if (false == m_Fjump&& true == m_onfloor)
//{
//	GetAnimator()->Play(L"Kahoidle");
//	m_gravity = 0;
//	m_jumpforce = JUMPFORCE;
//
//}

	//���� �ϴ� ����
	if (KeyDown('D'))
	{
		m_gravity = GRAVITY;
		m_jumpforce = JUMPFORCE;
		m_Fjump = true;
		m_onfloor = false;
		GetAnimator()->Play(L"KahoJump"); 
	}
	//���� ����(���߿� �ִ� ����)
	if (true == m_Fjump && false == m_onfloor)
	{
		m_gravity = GRAVITY;
		m_jumpforce -= m_gravity * fDT;
		pos.y -= m_jumpforce * fDT;

		if (m_jumpforce <= 0.f) //�������� 0�̵Ǹ�(�ְ����� �ö󰡸�)
		{
			pos.y += m_gravity * fDT;	//�߷����� ������
		}
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
	//�ϴ� ���ͷ� Ÿ���� �����ؼ� ������ ������
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
	//�ϴ� ���ͷ� Ÿ���� �����ؼ� ������ ������
	CGameObject* pOtherObj = pOther->GetObj();
	if (pOtherObj->GetName() == L"Monster")
	{
		m_onfloor = false;
	}
}
