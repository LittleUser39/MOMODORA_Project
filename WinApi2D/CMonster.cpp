#include "framework.h"
#include "CMonster.h"
#include "CKaho.h"

#include "CCollider.h"

#include "CD2DImage.h"
#include "CAnimator.h"
#include "CMHitBox.h"
#include "CSound.h"

#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"
#include "CAttState.h"

#include "CGravity.h"
#include "CRigidBody.h"

CMonster::CMonster()
{
	CD2DImage* m_pImg = CResourceManager::getInst()->LoadD2DImage(L"MonsterTex", L"texture\\sMonkey_Full.png");

	m_pAI = nullptr;

	SetName(L"Monster");
	SetScale(fPoint(50.f, 50.f));
	
	CD2DImage* m_pImgAtt = CResourceManager::getInst()->LoadD2DImage(L"MonsterAtt", L"texture\\sMonkeyAttack_Full1.png");
	CSoundManager::getInst()->AddSound(L"MonsterDeath", L"sound\\Monster\\MonsterDeath.wav");
	CreateCollider();
	GetCollider()->SetScale(fPoint(50.f, 50.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"sMonkey_idleR", m_pImg, fPoint(0, 0), fPoint(44.f, 32.f), fPoint(44.f, 0), 0.1f, 1, true);
	GetAnimator()->CreateAnimation(L"sMonkey_idleL", m_pImg, fPoint(0, 0), fPoint(44.f, 32.f), fPoint(44.f, 0), 0.1f, 1, true, true);

	GetAnimator()->CreateAnimation(L"sMonkey_FullR", m_pImg, fPoint(0, 0), fPoint(44.f, 32.f), fPoint(44.f, 0), 0.1f, 5, true);
	GetAnimator()->CreateAnimation(L"sMonkey_FullL", m_pImg, fPoint(0, 0), fPoint(44.f, 32.f), fPoint(44.f, 0), 0.1f, 5, true, true);

	
	GetAnimator()->CreateAnimation(L"MonkeyAtt_fullR", m_pImgAtt, fPoint(0, 0), fPoint(80.f, 48.f), fPoint(80.f, 0), 0.1f, 8, true);
	GetAnimator()->CreateAnimation(L"MonkeyAtt_fullL", m_pImgAtt, fPoint(0, 0), fPoint(80.f, 48.f), fPoint(80.f, 0), 0.1f, 8, true, true);
	
	GetAnimator()->Play(L"sMonkey_idleL");
	
	CreateGravity();
	CreateRigidBody();
}

CMonster::~CMonster()
{
	if (nullptr != m_pAI)
	{
		delete m_pAI;
	}
}

CMonster* CMonster::Clone()
{
	CMonster* newMonster = new CMonster;
	if (nullptr != m_pAI)
	{
		newMonster->m_pAI = new AI;
	}
	return new CMonster(*newMonster);
}

CMonster* CMonster::Create(MON_TYPE type, fPoint pos)
{
	CMonster* pMon = nullptr;

	switch (type)
	{
	case MON_TYPE::NORMAL:
	{
		pMon = new CMonster;
		pMon->SetPos(pos);

		tMonInfo info = {};
		info.fAtt = 10.f;
		info.fAttRange = 50.f;
		info.fRecogRange = 150.f;
		info.fHP = 10.f;
		info.fSpeed = 150.f;

		AI* pAI = new AI;
		pAI->AddState(new CIdleState(MON_STATE::IDLE));
		pAI->AddState(new CTraceState(MON_STATE::TRACE));
		pAI->AddState(new CAttState(MON_STATE::ATT));
		pAI->SetCurState(MON_STATE::IDLE);
		pMon->SetMonInfo(info);
		pMon->SetAI(pAI);
	}
	break;
	case MON_TYPE::RANGE:
		break;
	default:
		break;
	}
	assert(pMon);
	return pMon;
}

void CMonster::render()
{
	fPoint pos = GetPos();
	fPoint scale = GetScale();
	pos = CCameraManager::getInst()->GetRenderPos(pos);

	component_render();
}

void CMonster::update()
{
	if (nullptr != GetAnimator())
		GetAnimator()->update();
	if (nullptr != m_pAI)
		m_pAI->update();
}



float CMonster::GetSpeed()
{
	return m_tInfo.fSpeed;
}

const tMonInfo& CMonster::GetMonInfo()
{
	return m_tInfo;
}

void CMonster::SetSpeed(float speed)
{
	m_tInfo.fSpeed = speed;
}

void CMonster::SetAI(AI* ai)
{
	m_pAI = ai;
	m_pAI->m_pOwner = this;
}

void CMonster::SetMonInfo(const tMonInfo& info)
{
	m_tInfo = info;
}

void CMonster::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile_Player1" || pOtherObj->GetName() == L"Player_hitbox")
	{

		m_tInfo.fHP -= 1;
		if (m_tInfo.fHP <= 0)
		{
			CSoundManager::getInst()->Play(L"MonsterDeath");
			DeleteObj(this);
		}
	}
}

void CMonster::CreateHitBox()
{
	//이게 그릴것 위치 정하는거
	fPoint fpHitbox = GetPos();
	
	CKaho* pPlayer = CKaho::GetPlayer();
	fPoint fptPlayerPos = pPlayer->GetPos();


	fVec2 fvDiff = fptPlayerPos - fpHitbox;
	
	if(0 > fvDiff.x)
		fpHitbox.x -= GetScale().x / 2.f; 
	else if (0 < fvDiff.x)
		fpHitbox.x += GetScale().x / 2.f;
	
	CMHitBox* mHitbox = new CMHitBox;
	mHitbox->SetPos(fpHitbox);
	mHitbox->SetOwnerObj(this);
	CreateObj(mHitbox, GROUP_GAMEOBJ::HITBOX_MONSTER);
}