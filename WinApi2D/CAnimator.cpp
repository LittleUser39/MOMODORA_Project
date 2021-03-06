#include "framework.h"
#include "CAnimator.h"
#include "CAnimation.h"

CAnimator::CAnimator()
{
	m_pCurAni = nullptr;
	m_pOwner = nullptr;
}

CAnimator::~CAnimator()
{
	for (map<wstring, CAnimation*>::iterator iter = m_mapAni.begin(); iter != m_mapAni.end(); iter++)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}
	m_mapAni.clear();
}

CAnimator::CAnimator(const CAnimator& pOther)
{
	for (map<wstring, CAnimation*>::const_iterator iter = pOther.m_mapAni.begin(); iter != pOther.m_mapAni.end(); iter++)
	{
		CAnimation* newAni = new CAnimation(*iter->second);
		m_mapAni.insert(make_pair(newAni->GetName(), newAni));
		newAni->m_pAnimator = this;
	}
	m_pCurAni = FindAnimation(pOther.m_pCurAni->GetName());
	m_pOwner = nullptr;
}

CGameObject* CAnimator::GetObj()
{
	return m_pOwner;
}

void CAnimator::update()
{
	if (nullptr != m_pCurAni)
	{
		m_pCurAni->update();
	}
}

void CAnimator::render()
{
	if (nullptr != m_pCurAni)
	{
		m_pCurAni->render();
	}
}

void CAnimator::CreateAnimation(const wstring& strName, CD2DImage* tex, fPoint lt, fPoint slice, fPoint step, float duration, UINT frmCount,bool isLoop, bool reverse) 
{
	CAnimation* pAni = FindAnimation(strName);
	assert(nullptr == pAni);

	pAni = new CAnimation;

	pAni->SetName(strName);
	pAni->m_pAnimator = this;
	pAni->Create(tex, lt, slice, step, duration, frmCount);
	pAni->SetLoop(isLoop);
	pAni->m_bReverse = reverse;

	m_mapAni.insert(make_pair(strName, pAni));
}

CAnimation* CAnimator::FindAnimation(const wstring& strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAni.find(strName);

	if (iter == m_mapAni.end())
	{
		return nullptr;
	}
	return iter->second;
}

void CAnimator::Play(const wstring& strName)
{
	m_pCurAni = FindAnimation(strName);
}
