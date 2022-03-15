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

	//���� �̸� �ٲٱ�
	m_pImg2 = CResourceManager::getInst()->LoadD2DImage(L"KahoWalk", L"texture\\sKahoWalk_Full.png");
	m_pImg3 = CResourceManager::getInst()->LoadD2DImage(L"KahoJump", L"texture\\sKahoJump_Full.png");
	CreateAnimator();
    //�̸� �Ӽ�(��� ����) ������ġ �ڸ���ġ �ڸ����̵�����ġ �ӵ�,�ִϸ� ����
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
	//���� 
	if (KeyDown(VK_UP))
	{
		--pos.y;
		m_Fjump = true;
		m_onfloor = false;
		GetAnimator()->Play(L"KahoJump");
	}

	//������ (�������� �ƴϰ� �ٴ��϶�)
	if (false == m_Fjump&& true == m_onfloor)
	{
		GetAnimator()->Play(L"Kahoidle");
		m_gravity = 0;
		m_jumpforce = JUMPFORCE;
		//���� 
		if (KeyDown(VK_UP))
		{
			m_Fjump = true;
			m_onfloor = false;
			GetAnimator()->Play(L"KahoJump");
		}

	}
	//���߿� ������ �߷��ۿ�
	if (true == m_Fjump && false == m_onfloor)
	{
		m_gravity = GRAVITY;
		m_jumpforce -= m_gravity * fDT;
		pos.y -= m_jumpforce * fDT;
		
		if (m_jumpforce <= 0.f) //�������� 0�̵Ǹ�(�ְ����� �ö󰡸�)
		{
			pos.y += m_gravity * fDT;	//�߷����� ������
			m_Djump = true;
		}
		
	}
	//2������
	//if (KeyDown(VK_UP) && true == m_Djump && false == m_onfloor)
	//{
	//	m_gravity = GRAVITY;
	//	m_jumpforce = JUMPFORCE;
	//	m_jumpforce -= m_gravity * fDT;
	//	pos.y -= m_jumpforce * fDT;

	//	if (m_jumpforce <= 0.f) //�������� 0�̵Ǹ�(�ְ����� �ö󰡸�)
	//	{
	//		pos.y += m_gravity * fDT;	//�߷����� ������
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
	CGameObject* pOtherObj = pOther->GetObj();
	if (pOtherObj->GetName() == L"Monster")
	{
		m_onfloor = false;
	}
}
