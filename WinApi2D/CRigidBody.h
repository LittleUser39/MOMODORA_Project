#pragma once
class CRigidBody
{
private:
	friend class CGameObject;
	
	CGameObject* m_pOwner;

	fPoint	 m_vForce;	//��ü�� ������ ��
	fPoint	 m_vAccel;		//���ӵ�
	fPoint	 m_vAccelA;		//�߷� ���ӵ�
	fPoint	 m_vVelocity;	//�ӷ�
	float	 m_fMass;	

	float	 m_fFricCoeff;
	fPoint	 m_vMaxVelocity;

public:
	CRigidBody();
	~CRigidBody();

	void finalupdate();
	void Move();						//�����̴� �Լ�
	
	fPoint GetVelocity()			{ return m_vVelocity; }
	void SetVelocity(fPoint _v)		{ m_vVelocity = _v; }
	void AddVelocity(fPoint _v)		{ m_vVelocity += _v; }
	void SetMaxVelocity(fPoint _v)	{ m_vMaxVelocity = _v; }
	void SetAccelAlpha(fPoint _v)	{ m_vAccelA = _v; }
	
	void AddForce(fPoint _vF)	{ m_vForce += _vF; }
	void SetMass(float _fMass)	{ m_fMass = _fMass; }
	float GetMass()				{ return m_fMass; }
	float GetSpeed()			{ return m_vVelocity.Length(); }
	
};
