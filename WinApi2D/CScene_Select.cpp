#include "framework.h"
#include "CScene_Select.h"
#include "CSelectButton.h"
#include "CD2DImage.h"

CScene_Select::CScene_Select()
{

}

CScene_Select::~CScene_Select()
{

}

void CScene_Select::update()
{
	CScene::update();

	if (KeyDown(VK_SPACE))
		ChangeScn(GROUP_SCENE::START);
}

void CScene_Select::Enter()
{
	CreateSelectButton();
}

void CScene_Select::Exit()
{
	DeleteAll();
}

void CScene_Select::CreateSelectButton()
{
	CD2DImage* pImg = CResourceManager::getInst()->LoadD2DImage(L"SelectBox", L"texture\\sFileSelectBg2_0.png");
	CButtonUI* StartButton = new CButtonUI;
	StartButton->SetName(L"start");
	StartButton->SetScale(fPoint(300.f, 100.f));
	StartButton->SetPos(fPoint(200.f, 400.f));
	CButtonUI* TextUI = new CButtonUI;
	TextUI->SetScale(fPoint(300.f, 100.f));
	TextUI->SetPos(fPoint(0.f, 0.f));
	TextUI->SetText(L"Start");
	StartButton->AddChild(TextUI);



	AddObject(StartButton, GROUP_GAMEOBJ::UI);
}