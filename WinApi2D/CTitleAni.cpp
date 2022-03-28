#include "framework.h"
#include "CTitleAni.h"
#include "CD2DImage.h"
#include "CAnimator.h"
#include "CCollider.h"

CTitleAni::CTitleAni()
{
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"sTitleKaho_Full",L"texture\\background\\sTitleKaho_Full.png");
	SetScale(fPoint(600,200));
	SetPos(fPoint(1000,640));
	
	CreateCollider();
	GetCollider()->SetScale(fPoint(10,10));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"TitleKaho_Full", m_pImg, fPoint(0,0), fPoint(135,50), fPoint(135,0), 1.f, 5, true, false);
	GetAnimator()->Play(L"TitleKaho_Full");
}

CTitleAni::~CTitleAni()
{
	
}

CTitleAni* CTitleAni::Clone()
{
	return nullptr;
}

void CTitleAni::update()
{
	GetAnimator()->update();
}

void CTitleAni::render()
{
	component_render();
}
