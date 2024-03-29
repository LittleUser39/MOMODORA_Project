#include "framework.h"
#include "CGameObject.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CRigidBody.h"
#include "CGravity.h"

CGameObject::CGameObject()
{
	m_fptPos = {};
	m_fptScale = {};
	m_pCollider = nullptr;
	m_pAnimator = nullptr;
	m_pGravity = nullptr;
	m_pRigidBody = nullptr;
	m_bAlive = true;
}

CGameObject::CGameObject(const CGameObject& other)
{
	m_strName	= other.m_strName;
	m_fptPos	= other.m_fptPos;
	m_fptScale	= other.m_fptScale;
	m_pCollider = nullptr;
	m_pAnimator = nullptr;
	m_pRigidBody = nullptr;
	m_bAlive	= true;

	if (nullptr != other.m_pCollider)
	{
		m_pCollider = new CCollider(*other.m_pCollider);
		m_pCollider->m_pOwner = this;
	}
	if (nullptr != other.m_pAnimator)
	{
		m_pAnimator = new CAnimator(*other.m_pAnimator);
		m_pAnimator->m_pOwner = this;
	}
	if (nullptr != other.m_pRigidBody)
	{
		m_pRigidBody = new CRigidBody(*other.m_pRigidBody);
		m_pRigidBody->m_pOwner = this;
	}
	if (nullptr != other.m_pGravity)
	{
		m_pGravity = new CGravity(*other.m_pGravity);
		m_pGravity->m_pOwner = this;
	}
}

CGameObject::~CGameObject()
{
	if (nullptr != m_pCollider)
	{
		delete m_pCollider;
	}
	if (nullptr != m_pAnimator)
	{
		delete m_pAnimator;
	}
	if (nullptr != m_pRigidBody)
	{
		delete m_pRigidBody;
	}
	if (nullptr != m_pGravity)
	{
		delete m_pGravity;
	}
}

void CGameObject::SetPos(fPoint pos)
{
	m_fptPos = pos;
}

void CGameObject::SetScale(fPoint scale)
{
	m_fptScale = scale;
}

void CGameObject::SetName(wstring name)
{
	m_strName = name;
}

fPoint CGameObject::GetPos()
{
	return m_fptPos;
}

fPoint CGameObject::GetScale()
{
	return m_fptScale;
}

wstring CGameObject::GetName()
{
	return m_strName;
}

bool CGameObject::isDead()
{
	return !m_bAlive;
}

void CGameObject::SetDead()
{
	m_bAlive = false;
}

void CGameObject::finalupdate()
{
	
	if (nullptr != m_pGravity)
	{
		m_pGravity->finalupdate();
	}
	if (nullptr != m_pRigidBody)
	{
		m_pRigidBody->finalupdate();
	}
	if (nullptr != m_pCollider)
	{
		m_pCollider->finalupdate();
	}
}

void CGameObject::render()
{
	// 절대 위치를 넘기고, 랜더링 위치를 받아옴
	fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(m_fptPos);

	// 카메라를 기준으로 그려져야하는 위치
	CRenderManager::getInst()->RenderRectangle(
		fptRenderPos.x - m_fptScale.x / 2,
		fptRenderPos.y - m_fptScale.y / 2,
		fptRenderPos.x + m_fptScale.x / 2,
		fptRenderPos.y + m_fptScale.y / 2);

	if (nullptr != m_pAnimator)
	{
		m_pAnimator->render();
	}

	component_render();
}

void CGameObject::component_render()
{
	if (nullptr != m_pAnimator)
	{
		m_pAnimator->render();
	}
	if (nullptr != m_pCollider&& CCore::getInst()->GetDebugMode())
	{
		m_pCollider->render();
	}
}

CCollider* CGameObject::GetCollider()
{
	return m_pCollider;
}

void CGameObject::CreateCollider()
{
	m_pCollider = new CCollider();
	m_pCollider->m_pOwner = this;
}

CAnimator* CGameObject::GetAnimator()
{
	return m_pAnimator;
}

void CGameObject::CreateAnimator()
{
	m_pAnimator = new CAnimator;
	m_pAnimator->m_pOwner = this;
}

CRigidBody* CGameObject::GetRigidBody()
{
	 return m_pRigidBody;
}

void CGameObject::CreateRigidBody()
{
	m_pRigidBody = new CRigidBody;
	m_pRigidBody->m_pOwner = this;
}

void CGameObject::CreateGravity()
{
	m_pGravity = new CGravity;
	m_pGravity->m_pOwner = this;
}

bool CGameObject::GetGround()
{
	return m_pGravity->m_bGround;
}
