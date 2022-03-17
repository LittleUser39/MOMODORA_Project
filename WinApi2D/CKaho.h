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
	CD2DImage* m_pImg9;
	CD2DImage* m_pImg10;

	const float fdealy = 0.5f; //������ 
	const float fcombo = 1.f; //�޺� �ð� - �̾ȿ� ������ ����

	bool m_rolldis;		//ĳ���� ������ �ֳ�
	float m_rollCount;
	float m_velocity;	//ĳ���� �ӵ�
	float m_jumpforce;	//ĳ���� ������
	float m_gravity;	//�߷�
	float m_HP;			//ĳ������ ü��
	
	float delay = 0; //���� ������
	int combo = 0;
	
	bool m_onfloor;			//ĳ���Ͱ� �ٴڿ� �ִ°�
	bool m_idle;			//ĳ���Ͱ� ������ �ִ°�
	bool m_Fjump;			//ĳ���Ͱ� ù��°�������� �ΰ�
	
	bool m_dead;			//ĳ���Ͱ� �׾��ִ°�

	bool CanAttack();		//�����Ҽ� �ִ�
	bool Attack();			//1��° ����
	bool ComboAttack2();	//2��°
	bool ComboAttack3();	//3��°

	bool IsComboAttck();	//���Ӱ����̴�
public:
	CKaho();
	~CKaho();
	virtual CKaho* Clone();

	virtual void update();
	virtual void render();

	void CreateArrow();		//ȭ�� �浹ü ����
	void CreateHitBox();	//�÷��̾ �����ϸ� �װ��� ��Ʈ�ڽ�����

	virtual void OnCollision(CCollider* pOther);		//�浹�� �϶�
	virtual void OnCollisionEnter(CCollider* pOther);	//������ ����
	virtual void OnCollisionExit(CCollider* pOther);	//�浹���� ������ 
};

