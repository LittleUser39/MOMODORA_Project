#pragma once
#include "CScene.h"
class CScene_Boss : public CScene
{
	public:
		CScene_Boss();
		virtual ~CScene_Boss();

		virtual void update();

		virtual void Enter();
		virtual void Exit();
};




