#include "framework.h"
#include "CGravity.h"
#include "CGameObject.h"

CGravity::CGravity()
{
	m_pOwner = nullptr;
	m_bGround = false;
}

CGravity::~CGravity()
{
	
}

void CGravity::finalupdate()
{
	m_pOwner->GetRigidBody()->SetAccelAlpha(fPoint(0.f, 800.f));
}

void CGravity::SetGround(bool _b)
{
	m_bGround = _b;
	if (m_bGround)
	{
		fPoint vV = m_pOwner->GetRigidBody()->GetVelocity();
		m_pOwner->GetRigidBody()->SetVelocity(fPoint(vV.x, 0.f));
	}
}