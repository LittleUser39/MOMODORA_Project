#pragma once
#include "CScene.h"
class CScene_Death : public CScene
{
	CScene_Death();
	~CScene_Death();

	virtual void update();

	virtual void Enter();
	virtual void Exit();
};

