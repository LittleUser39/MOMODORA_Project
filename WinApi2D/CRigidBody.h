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
	float	 m_fMaxSpeed;

public:
	CRigidBody();
	~CRigidBody();

	void finalupdate();
	
	void AddForce(fPoint _vForce);		//���� �ش�
	void SetMass(float _fMass);			//����
	float GetMass();					//������ ������

	void Move();						//�����̴� �Լ�

	void SetVelocity(fPoint _vVelocity);	//�ӵ� ����
	void AddVelocity(fPoint _vVelocity);	//���ӵ� �ֱ�
	void SetMaxSpeed(float _fMaxSpeed); //�ְ�ӵ� ����
	float GetSpeed();					//�ӵ� ��������
};
