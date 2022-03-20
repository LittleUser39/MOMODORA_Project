#pragma once
class CRigidBody
{
private:
	friend class CGameObject;
	
	CGameObject* m_pOwner;

	fPoint	 m_vForce;	//강체에 누적된 힘
	fPoint	 m_vAccel;		//가속도
	fPoint	 m_vAccelA;		//중력 가속도
	fPoint	 m_vVelocity;	//속력
	float	 m_fMass;	

	float	 m_fFricCoeff;
	fPoint	 m_vMaxVelocity;

public:
	CRigidBody();
	~CRigidBody();

	void finalupdate();
	void Move();						//움직이는 함수
	
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
