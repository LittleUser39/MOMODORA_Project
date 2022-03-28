#include "framework.h"
#include "CBossWarp.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CScene.h"
#include "CAnimator.h"

CBossWarp::CBossWarp()
{
	SetScale(fPoint(100, 100));
	
	CreateCollider();
	GetCollider()->SetScale(fPoint(50, 80));

	CD2DImage* pImg = CResourceManager::getInst()->LoadD2DImage(L"BossWarp", L"texture\\BossWarp.png");
	
	CreateAnimator();
	
	GetAnimator()->CreateAnimation(L"BossWarp1", pImg, fPoint(0.f, 0.f), fPoint(96.f, 96.f), fPoint(96, 0), 1, 0.1f, true);
	GetAnimator()->Play(L"Bosswarp1");
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
	GetAnimator()->update();
}

void CBossWarp::OnCollisionEnter(CCollider* other)
{
	if (L"Kaho" == other->GetObj()->GetName())
	{
		ChangeScn(GROUP_SCENE::BOSS);
	}
}
