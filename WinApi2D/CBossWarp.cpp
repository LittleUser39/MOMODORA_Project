#include "framework.h"
#include "CBossWarp.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CScene.h"

CBossWarp::CBossWarp()
{
	SetScale(fPoint(50, 80));
	CD2DImage* pImg = CResourceManager::getInst()->LoadD2DImage(L"BossWarp", L"texture\\BossWarp.png");
	CreateCollider();
	GetCollider()->SetScale(fPoint(50, 80));
}

CBossWarp::~CBossWarp()
{

}

CBossWarp* CBossWarp::Clone()
{
	return nullptr;
}

void CBossWarp::update()
{
}

void CBossWarp::render()
{
	component_render();
}

void CBossWarp::OnCollisionEnter(CCollider* other)
{
	if (L"Kaho" == other->GetObj()->GetName())
	{
		ChangeScn(GROUP_SCENE::BOSS);
	}
}
