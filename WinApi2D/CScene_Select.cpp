#include "framework.h"
#include "CScene_Select.h"
#include "CSelectButton.h"
#include "CD2DImage.h"
#include "CBackGround.h"
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
	CSoundManager::getInst()->Stop(L"Title");
}

void CScene_Select::CreateSelectButton()
{
	CD2DImage* pImg = CResourceManager::getInst()->LoadD2DImage(L"SelectBox", L"texture\\sFileSelectBg2_0.png");
	CBackGround* backGround = new CBackGround;
	backGround->Load(L"SelectBackground", L"texture\\background\\Select.png");
	backGround->SetPos(fPoint(0.f, 0.f));
	backGround->SetScale(fPoint(backGround->GetScale().x/1.2f, backGround->GetScale().y));
	AddObject(backGround, GROUP_GAMEOBJ::BACKGROUND);


	CButtonUI* StartButton = new CButtonUI;
	StartButton->SetName(L"start");
	StartButton->SetScale(fPoint(300.f, 100.f));
	StartButton->SetPos(fPoint(630.f, 350.f));
	StartButton->SetImage(pImg);
	StartButton->SetText(L"게임 시작"); 
	
	CButtonUI* ToolButton = new CButtonUI;
	ToolButton->SetName(L"Tool");
	ToolButton->SetScale(fPoint(300.f, 100.f));
	ToolButton->SetPos(fPoint(630.f, 450.f));
	ToolButton->SetImage(pImg);
	ToolButton->SetText(L"Tool");

	CButtonUI* ExitButton = new CButtonUI;
	ExitButton->SetName(L"start");
	ExitButton->SetScale(fPoint(300.f, 100.f));
	ExitButton->SetPos(fPoint(630.f, 550.f));
	ExitButton->SetImage(pImg);
	ExitButton->SetText(L"게임 종료");


	AddObject(StartButton, GROUP_GAMEOBJ::UI);
	AddObject(ToolButton, GROUP_GAMEOBJ::UI);
	AddObject(ExitButton, GROUP_GAMEOBJ::UI);

}