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
	
	void AddForce(fPoint _vForce);		//���� �ش�
	void SetMass(float _fMass);			//����
	float GetMass();					//������ ������
	float GetSpeed();					//�ӵ� ��������
	fPoint GetVelocity() { return m_vVelocity; }

	void SetVelocity(fPoint _vVelocity);	//�ӵ� ����
	void AddVelocity(fPoint _vVelocity);	//���ӵ� �ֱ�
	void SetMaxVelocity(fPoint _v) { m_vMaxVelocity = _v; } //�ְ� �ӷ� ����
	
	void Move();						//�����̴� �Լ�
	
	void SetAccelAlpha(fPoint _v) { m_vAccelA = _v; }
};
