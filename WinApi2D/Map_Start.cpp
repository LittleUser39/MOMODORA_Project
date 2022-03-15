#include "framework.h"
#include "Map_Start.h"
#include "CD2DImage.h"

Map_Start::Map_Start()
{
    pimg = CResourceManager::getInst()->LoadD2DImage(L"test", L"texture\\map\\stage1_background.png");
    SetPos(fPoint(0, 0));
    SetScale(fPoint(1280, 720));
}

Map_Start::~Map_Start()
{
}

Map_Start* Map_Start::Clone()
{
    return nullptr;
}

void Map_Start::update()
{

}

void Map_Start::render()
{
    fPoint pos = GetPos();
    fPoint scale = GetScale();
    pos = CCameraManager::getInst()->GetRenderPos(pos);

    CRenderManager::getInst()->RenderImage(
        pimg,
        pos.y ,
        pos.x ,
        pos.x + scale.x,
        pos.y + scale.y 
    );
}
