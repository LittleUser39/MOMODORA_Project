#pragma once
#include "CScene.h"
class CScene_Select : public CScene
{
	
public:
	CScene_Select();
	~CScene_Select();

	virtual void update();

	virtual void Enter();
	virtual void Exit();

	void CreateSelectButton();
};

