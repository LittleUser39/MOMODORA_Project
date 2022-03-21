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
	CD2DImage* pImg1 = CResourceManager::getInst()->LoadD2DImage(L"selectmenu", L"texture\\menu.png");
	CSelectButton* button = new CSelectButton;
	button->SetScale(fPoint(200,100));
	button->SetPos(fPoint(100,200));
	button->SetImage(pImg1);	
	AddObject(button, GROUP_GAMEOBJ::UI);
	
	CSelectButton* buttonA = button->Clone();
	buttonA->SetPos(fPoint(100, 300));
	AddObject(buttonA, GROUP_GAMEOBJ::UI);
	
	CSelectButton* buttonB = button->Clone();
	buttonB->SetPos(fPoint(100, 400));
	AddObject(buttonB, GROUP_GAMEOBJ::UI);
}

void CScene_Select::Exit()
{
	DeleteAll();
}
