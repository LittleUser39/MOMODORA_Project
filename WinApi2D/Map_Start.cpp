#include "framework.h"
#include "Map_Start.h"
#include "CD2DImage.h"

Map_Start::Map_Start()
{
  
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
    fPoint pos = GetPos();

    if (Key(VK_LEFT))
    {
        pos.x -= 100 * fDT;
    }

    if (Key(VK_RIGHT))
    {
        pos.x += 100 * fDT;
    }

    if (Key(VK_DOWN))
    {
        pos.y += 100 * fDT;
    }

    if (Key(VK_UP))
    {
        pos.y -= 100 * fDT;
    }

    SetPos(pos);
}

void Map_Start::render()
{
    fPoint pos = GetPos();
    fPoint scale = GetScale();

    CRenderManager::getInst()->RenderImage(
        pimg,
        pos.x - scale.x / 2.f,
        pos.y - scale.y / 2.f,
        pos.x + scale.x / 2.f,
        pos.y + scale.y / 2.f
    );
}
