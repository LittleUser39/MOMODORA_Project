#include "framework.h"
#include "CScene_Title.h"
#include "CBackGround.h"
#include "CGameObject.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CImageObject.h"
#include "CTitleAni.h"

void CScene_Title::update()
{
	CScene::update();
	if(KeyDown(VK_SPACE))
		ChangeScn(GROUP_SCENE::SELECT);
	
}

void CScene_Title::Enter()
{	
	//타이틀 배경
	CBackGround* backGround = new CBackGround;
	backGround->Load(L"BackGround_Start", L"texture\\background\\sTitleScreenBG_0.png");
	backGround->SetPos(fPoint(0.f, 0.f));
	AddObject(backGround, GROUP_GAMEOBJ::BACKGROUND);

	//타이틀 고양이
	CBackGround* Cat = new CBackGround;
	Cat->Load(L"Cat", L"texture\\background\\sTitleScreen2_0.png");
	Cat->SetPos(fPoint(WINSIZEX / 2.f - 300, WINSIZEY / 2.f - 310));
	Cat->SetScale(fPoint(300.f, 300.f));
	AddObject(Cat, GROUP_GAMEOBJ::BACKGROUND);

	//타이틀 이름
	CBackGround* title = new CBackGround;
	title->Load(L"title", L"texture\\background\\sTitleScreen_2.png");
	title->SetPos(fPoint(WINSIZEX/2.f - 400, WINSIZEY/2.f- 500));
	title->SetScale(fPoint(800.f, 800.f));
	AddObject(title, GROUP_GAMEOBJ::BACKGROUND);
	
	//todo 타이틀 애니 구현해야함
	//생각 네모 박스 객체 하나 만들어서 위치 구현후 거기다가 애니메이션 덮어씀

	CTitleAni* titleAni = new CTitleAni;
	AddObject(titleAni, GROUP_GAMEOBJ::BACKGROUND);
	
}


void CScene_Title::Exit()
{
	DeleteAll();
}
