#include "framework.h"
#include "CScene_Title.h"
#include "CBackGround.h"
#include "CGameObject.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CImageObject.h"
#include "CTitleAni.h"
#include "CD2DImage.h"
#include "CSound.h"
void CScene_Title::update()
{
	CScene::update();
	if(KeyDown(VK_SPACE))
		ChangeScn(GROUP_SCENE::SELECT);
	if (KeyDown(VK_TAB))
		ChangeScn(GROUP_SCENE::START);
	if (KeyDown('A'))
		ChangeScn(GROUP_SCENE::BOSS);
	
}

void CScene_Title::Enter()
{	
	CSoundManager::getInst()->AddSound(L"Title", L"sound\\BGM\\02 Title.mp3",false,true	);
	CSoundManager::getInst()->Play(L"Title");
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
	
	CBackGround* Press = new CBackGround;
	Press->Load(L"Press", L"texture\\background\\startscene_text.png");
	Press->SetPos(fPoint(title->GetPos().x + 100, title->GetPos().y + 600));
	Press->SetScale(fPoint(600.f, 60.f));
	AddObject(Press, GROUP_GAMEOBJ::BACKGROUND);

}


void CScene_Title::Exit()
{
	DeleteAll();
	
}
