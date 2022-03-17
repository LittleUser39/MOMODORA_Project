#pragma once
#include "CGameObject.h"

class CD2DImage;

class CImageObject : public CGameObject
{
private:
    CD2DImage* m_pimg;

public:

    CImageObject();
    ~CImageObject();

    CImageObject* Clone();

    void render();
    void update();
    void Load(const wstring& strKey, const wstring& strPath);
};

