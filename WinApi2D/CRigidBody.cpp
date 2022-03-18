#include "framework.h"
#include "CRigidBody.h"
#include "CGameObject.h"

CRigidBody::CRigidBody()
{
	m_pOwner = nullptr;
	m_fMass = { 1.f };
	m_fFricCoeff = 200.f; // ������
	m_fMaxSpeed = 100.f;  // �ְ�ӵ�
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::finalupdate()
{
	float fForce = m_vForce.Length();

	if (0.f != fForce)
	{
		m_vForce.normalize();

		float m_fAccel = fForce / m_fMass;

		m_vAccel = m_vForce * m_fAccel;

		m_vVelocity += m_vAccel * fDT;
	}
	// �����¿� ���� �ݴ� ���������� ���ӵ�
	if (!m_vVelocity.isZero())
	{
		fPoint vFricDir = m_vVelocity;
		vFricDir.normalize();

		fPoint vFriction = vFricDir * (-1) * m_fFricCoeff * fDT;

		if (m_vVelocity.Length() <= vFriction.Length())
		{
			m_vVelocity = fPoint(0.f, 0.f);
		}
		else
		{
			m_vVelocity = m_vVelocity + vFriction;
		}
	}

	// �ӵ� ���� �˻�
	if (m_fMaxSpeed < m_vVelocity.Length())
	{
		m_vVelocity.normalize();
		m_vVelocity = m_vVelocity * m_fMaxSpeed;
	}

	Move();

	m_vForce = fPoint(0.f, 0.f);
}

void CRigidBody::AddForce(fPoint _vForce)
{
	m_vForce += _vForce;
}

void CRigidBody::SetMass(float _fMass)
{
	 m_fMass = _fMass; 
}

float CRigidBody::GetMass()
{
	return m_fMass;
}

void CRigidBody::Move()
{
	// �̵� �ӷ�
	float fSpeed = m_vVelocity.Length();

	if (0.f != fSpeed)
	{
		// �̵� ����
		fPoint vDir = m_vVelocity;
		vDir.normalize();

		fPoint vPos = m_pOwner->GetPos();

		vPos += m_vVelocity * fDT;

		m_pOwner->SetPos(vPos);
	}
}

void CRigidBody::SetVelocity(fPoint _vVelocity)
{
	m_vVelocity = _vVelocity;
}

void CRigidBody::AddVelocity(fPoint _vVelocity)
{
	m_vVelocity += _vVelocity;
}

void CRigidBody::SetMaxSpeed(float _fMaxSpeed)
{
	m_fMaxSpeed = _fMaxSpeed;
}

float CRigidBody::GetSpeed()
{
	return (float)m_vVelocity.Length();
}
