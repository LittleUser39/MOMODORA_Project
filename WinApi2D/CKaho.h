#pragma once
#include "CGameObject.h"
class CKaho : public CGameObject
{
private:
	CD2DImage* m_pImg;	//ĳ���� �̹���
	CD2DImage* m_pImg2;
	CD2DImage* m_pImg3;
	CD2DImage* m_pImg4;
	CD2DImage* m_pImg5; 
	CD2DImage* m_pImg6;
	CD2DImage* m_pImg7;
	CD2DImage* m_pImg8;
	
	bool m_rolldis;		//ĳ���� ������ �ֳ�
	float m_rollCount;
	float m_velocity;	//ĳ���� �ӵ�
	float m_jumpforce;	//ĳ���� ������
	float m_gravity;	//�߷�
	float m_HP;			//ĳ������ ü��
	UINT m_AttackCount; //���� �޺�

	bool m_onfloor;		//ĳ���Ͱ� �ٴڿ� �ִ°�
	bool m_idle;		//ĳ���Ͱ� ������ �ִ°�
	bool m_Fjump;		//ĳ���Ͱ� ù��°�������� �ΰ�
	bool m_Djump;		//ĳ���Ͱ� �ι�° ���� ���� �ΰ�
	bool m_dead;		//ĳ���Ͱ� �׾��ִ°�

public:
	CKaho();
	~CKaho();
	virtual CKaho* Clone();

	virtual void update();
	virtual void render();

	virtual void OnCollision(CCollider* pOther);		//�浹�� �϶�
	virtual void OnCollisionEnter(CCollider* pOther);	//������ ����
	virtual void OnCollisionExit(CCollider* pOther);	//�浹���� ������ 
};

