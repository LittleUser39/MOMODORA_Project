#pragma once
#include "CGameObject.h"

class CD2DImage;

class CTile : public CGameObject
{

private:
	CD2DImage* m_pImg;
	int m_iX;
	int m_iY;
	int m_iIdx;			// 텍스쳐 인덱스
	
	GROUP_TILE m_group;
public:
	const static int SIZE_TILE = 32;

	CTile();
	virtual ~CTile();

	virtual CTile* Clone();

	virtual void update();
	virtual void render();

	void SetD2DImage(CD2DImage* pTex);
	void SetImgIdx(UINT idx);
	void SetX(int x);
	void SetY(int y);
	void SetGroup(GROUP_TILE group);

	int GetIdx();
	int GetX();
	int GetY();
	GROUP_TILE GetGroup();

	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);

	virtual void OnCollision(CCollider* _pOther);		// 재정의용 충돌중 가상함수
	virtual void OnCollisionEnter(CCollider* _pOther);	// 재정의용 충돌시 가상함수
	virtual void OnCollisionExit(CCollider* _pOther);		// 재정의용 탈충돌 가상함수

};

