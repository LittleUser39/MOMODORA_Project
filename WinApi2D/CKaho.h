#pragma once
#include "CGameObject.h"

class CHitBox;

enum class PLAYER_STATE
{
	IDLE,
	WALK,
	BRAKE,
	CROUCH,
	ROLL,
	BOW,
	CROUCHBOW,
	ATTACK1,
	ATTACK2,
	ATTACK3,
	JUMP,
	DEAD,
	END
};

class CKaho : public CGameObject
{
private:
	static CKaho* instance; //�ϳ��� �ִ� �÷��̾�

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
	CD2DImage* m_pImg11;

	PLAYER_STATE m_eCurState; //ĳ���� �������
	PLAYER_STATE m_ePreState; //ĳ���� ��������
	
	int          m_iCurDir;	  //�������
	int          m_iPreDir;	  //��������

	float m_fPMAXHP;
	float m_fPHP;

	const float m_fDelaytime = 0.5f; //������ 
	const float m_fCombotime = 1.f; //�޺� �ð� - �̾ȿ� ������ ����

	float m_fRollCoolTime = 1.f;
	float m_fRollTime = 0;

	float m_fDelay = 0; //���� ������
	int	  m_iCombo = 0;
	
	bool m_onfloor;			//ĳ���Ͱ� �ٴڿ� �ִ°�
	bool m_bAttacking;		//ĳ���Ͱ� ������ �ΰ�
	bool m_bJump;			//��������
	bool m_bDead;			//ĳ���Ͱ� �׾��ִ°�
	bool m_bCrouch;			//ĳ���Ͱ� ��ũ�� ���� �ΰ�
	bool m_bBow;

public:
	CKaho();
	~CKaho();
	virtual CKaho* Clone();

	void update_move();
	void update_state();
	void update_animation();

	virtual void update();
	virtual void render();

	float GetDirect();

	void CreateArrow();		//ȭ�� �浹ü ����
	void CreateHitBox();	//��Ʈ �ڽ� �浹ü ����
	float GetHP();
	virtual void OnCollision(CCollider* pOther);		//�浹�� �϶�
	virtual void OnCollisionEnter(CCollider* pOther);	//������ ����
	virtual void OnCollisionExit(CCollider* pOther);	//�浹���� ������ 

	const int GetAttCount();

	virtual void RegisterPlayer();
	static CKaho* GetPlayer();	// ���� ���� �ϳ��� �ִ� �÷��̾� ��ü Ȯ��(���Ƿ� �̱��� ����)
	void RenderPlayerInfo();
};

