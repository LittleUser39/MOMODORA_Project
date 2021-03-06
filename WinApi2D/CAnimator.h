#pragma once

class CGameObject;
class CAnimation;
class CD2DImage;

class CAnimator
{
	friend class CGameObject;

private:
	map<wstring, CAnimation*>	m_mapAni;
	CAnimation*					m_pCurAni;
	CGameObject*				m_pOwner;

public:
	CAnimator();
	~CAnimator();
	CAnimator(const CAnimator& pOther);

	CGameObject* GetObj();

	void update();
	void render();

	void CreateAnimation(const wstring& strName, CD2DImage* tex, fPoint lt, fPoint slice, fPoint step,
		float duration, UINT frmCount, bool isLoop, bool reverse = false);
	CAnimation* FindAnimation(const wstring& strName);
	void Play(const wstring& strName);

	CAnimation* GetCurAni() { return m_pCurAni; }
};

