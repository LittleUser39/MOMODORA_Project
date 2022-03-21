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
	//Ÿ��Ʋ ���
	CBackGround* backGround = new CBackGround;
	backGround->Load(L"BackGround_Start", L"texture\\background\\sTitleScreenBG_0.png");
	backGround->SetPos(fPoint(0.f, 0.f));
	AddObject(backGround, GROUP_GAMEOBJ::BACKGROUND);

	//Ÿ��Ʋ �����
	CBackGround* Cat = new CBackGround;
	Cat->Load(L"Cat", L"texture\\background\\sTitleScreen2_0.png");
	Cat->SetPos(fPoint(WINSIZEX / 2.f - 300, WINSIZEY / 2.f - 310));
	Cat->SetScale(fPoint(300.f, 300.f));
	AddObject(Cat, GROUP_GAMEOBJ::BACKGROUND);

	//Ÿ��Ʋ �̸�
	CBackGround* title = new CBackGround;
	title->Load(L"title", L"texture\\background\\sTitleScreen_2.png");
	title->SetPos(fPoint(WINSIZEX/2.f - 400, WINSIZEY/2.f- 500));
	title->SetScale(fPoint(800.f, 800.f));
	AddObject(title, GROUP_GAMEOBJ::BACKGROUND);
	
	//todo Ÿ��Ʋ �ִ� �����ؾ���
	//���� �׸� �ڽ� ��ü �ϳ� ���� ��ġ ������ �ű�ٰ� �ִϸ��̼� ���

	CTitleAni* titleAni = new CTitleAni;
	AddObject(titleAni, GROUP_GAMEOBJ::BACKGROUND);
	
}


void CScene_Title::Exit()
{
	DeleteAll();
}
