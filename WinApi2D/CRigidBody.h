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
	float	 m_fMaxSpeed;

public:
	CRigidBody();
	~CRigidBody();

	void finalupdate();
	
	void AddForce(fPoint _vForce);		//힘을 준다
	void SetMass(float _fMass);			//질량
	float GetMass();					//질량을 가져옴

	void Move();						//움직이는 함수

	void SetVelocity(fPoint _vVelocity);	//속도 설정
	void AddVelocity(fPoint _vVelocity);	//가속도 주기
	void SetMaxSpeed(float _fMaxSpeed); //최고속도 설정
	float GetSpeed();					//속도 가져오기
};
