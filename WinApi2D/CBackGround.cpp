#include "framework.h"
#include "CBackGround.h"
#include "CD2DImage.h"

CBackGround::CBackGround()
{
    m_pImg = nullptr;
}

CBackGround::~CBackGround()
{

}

void CBackGround::Load(wstring strKey, wstring strPath)
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
    SetScale(fPoint(1280, 720)); //³»°¡ ¹Ù²Þ
}

CBackGround* CBackGround::Clone()
{
    return nullptr;
}

void CBackGround::update()
{
}

void CBackGround::render()
{
    if (nullptr == m_pImg)
    {
        return;
    }
    fPoint pos = GetPos();
    fPoint scale = GetScale();
    fPoint renderPos = CCameraManager::getInst()->GetRenderPos(pos);
    renderPos = pos + (renderPos - pos) / 5;   

    CRenderManager::getInst()->RenderImage(
        m_pImg,
        renderPos.x,
        renderPos.y,
        renderPos.x + scale.x,
        renderPos.y + scale.y
    );
}