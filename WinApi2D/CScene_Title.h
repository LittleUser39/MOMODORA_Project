#pragma once
#include "CScene.h"

class CD2DImage;


class CScene_Title : public CScene 
{
    
    CD2DImage* m_pTitleImage;

public:
    virtual void update();
  
    virtual void Enter();
    virtual void Exit();
};

