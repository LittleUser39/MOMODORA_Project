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
	m_idle = true;		//������ �ִ»���
	m_Fjump = false;	//���� ����(����)
	
	m_dead = false;		//���� ����
	m_onfloor = true;	//�ٴڿ� �ִ� ����
	m_HP = 100;			//ĳ���� ü��
	m_rolldis = false;		//ĳ���Ͱ� �������ֳ�
	m_rollCount = 100;		//�Ÿ�
	m_velocity = 150;
	m_gravity = GRAVITY;
	m_jumpforce = JUMPFORCE;
	
	//img 1= �⺻, 2 = �ȱ�, 3 = ����, 4 = ����, 5 = ����2,6 = ����3, 7 = Ȱ���(����), 8 = ������ 9 = Ȱ���(�ɾ�)
    
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"KahoImage", L"texture\\sKahoidle_Full.png");
    SetName(L"Kaho");
    SetScale(fPoint(70.f, 70.f));

	//�浹ü ���� �� �浹ü ũ��,������
    CreateCollider();
    GetCollider()->SetScale(fPoint(40.f, 40.f));
    GetCollider()->SetOffsetPos(fPoint(0.f, 5.f));
	
	//���� �̸� �ٲٱ�
	m_pImg2 = CResourceManager::getInst()->LoadD2DImage(L"KahoWalk", L"texture\\sKahoWalk_Full.png");
	m_pImg3 = CResourceManager::getInst()->LoadD2DImage(L"KahoJump", L"texture\\sKahoJump_Full.png");
	m_pImg4 = CResourceManager::getInst()->LoadD2DImage(L"KahoAttack1", L"texture\\sKahoAttack_Full1.png");
	m_pImg5 = CResourceManager::getInst()->LoadD2DImage(L"KahoAttack2", L"texture\\sKahoAttack_Full2.png");
	m_pImg6 = CResourceManager::getInst()->LoadD2DImage(L"KahoAttack3", L"texture\\sKahoAttack_Full3.png");
	m_pImg7 = CResourceManager::getInst()->LoadD2DImage(L"KahoBow", L"texture\\sKahoBow_Full.png");
	m_pImg8 = CResourceManager::getInst()->LoadD2DImage(L"KahoRoll", L"texture\\sKahoRoll_Full.png");
	m_pImg9 = CResourceManager::getInst()->LoadD2DImage(L"KahoCrouchBow", L"texture\\sKahoCrouchBow_Full.png");
	CreateAnimator();
    //�̸� �Ӽ�(��� ����) ������ġ �ڸ���ġ �ڸ����̵�����ġ �ӵ�,�ִϸ� ����
	GetAnimator()->CreateAnimation(L"Kahoidle", m_pImg, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 5, false);
	GetAnimator()->CreateAnimation(L"KahoidleL", m_pImg, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 5, true);

	//GetAnimator()->CreateAnimation(L"RightWalk", m_pImg2, fPoint(0.f, 0.f), fPoint(48.f, 48.f), fPoint(48.f, 0.f), 0.1f, 9); �ϴ� ���� 
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
	//�ٴ��϶� �¿� �ִϸ�
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
		//todo �ɱ�� ��ٸ� ������ ��ٸ� ��������
		//pos.y += m_velocity * fDT;
	}

	if (Key(VK_UP))
	{
		//todo ��ٸ������� ��ٸ� ������
	}

	//������ ����
	delay += fDT;
	
	//���� ������ �ƴҶ� �޺�0���� 
	if (!IsComboAttck())
		combo = 0;
	//���� ���� ����ٰ� ��Ʈ�ڽ�(�浹ü) ����
	if (CanAttack())
	{
		if (KeyDown('A'))
		{
			//�޺��� ������ 1��° ����
			if (0 == combo)
			{
				Attack();
				CreateHitBox();
				GetAnimator()->Play(L"KahoAttack1");
			}
			//�޺��� 1�϶� 2��° ����
			else if (IsComboAttck()&& combo == 1)
			{
				ComboAttack2();
				GetAnimator()->Play(L"KahoAttack2");
			}
			//�޺��� 2�϶� 3��° ����
			else if (IsComboAttck() &&combo == 2)
			{
				ComboAttack3();
				GetAnimator()->Play(L"KahoAttack3");
			}
		}
	}

	if (KeyDown('S'))
	{
		//todo Ȱ���� - ���⿡ create �̻��� �ֱ� ���� ���ݳֱ�
		CreateArrow();
		GetAnimator()->Play(L"KahoBow");
	}
	if (Key(VK_DOWN) && Key('S'))
		GetAnimator()->Play(L"KahoCrouchBow");
	//������
	if (Key('F') && false == m_rolldis)
	{
		//todo ������ - �¿�� ���� �̵� �ϸ鼭 �÷��̾�� ����
		pos.x += m_velocity * DT;
		
		if (pos.x > pos.x + m_rollCount)
			m_rolldis = true;
		GetAnimator()->Play(L"KahoRoll");
		
	}
	 
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

void CKaho::CreateHitBox()
{
	fPoint fpHitBoxPos = GetPos();
	fpHitBoxPos.x += GetScale().x / 2.f;

	// ��Ʈ�ڽ� ������Ʈ
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
	//�ϴ� ���ͷ� Ÿ���� �����ؼ� ������ ������
	CGameObject* pOtherObj = pOther->GetObj();
	if (pOtherObj->GetName() == L"Monster")
	{
		m_onfloor = true;
		m_Fjump = false;
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