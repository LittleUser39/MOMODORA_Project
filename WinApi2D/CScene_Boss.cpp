#include "framework.h"
#include "CScene_Boss.h"

#include "CGameObject.h"
#include "CKaho.h"
#include "CMonster.h"
#include "CImp.h"
#include "CFennel.h"

#include "CMap.h"
#include "CBackGround.h"

#include "CSound.h"
#include "CD2DImage.h"


CScene_Boss::CScene_Boss()
{
}

CScene_Boss::~CScene_Boss()
{
}

void CScene_Boss::update()
{
	CScene::update();
}

void CScene_Boss::Enter()
{
	CSoundManager::getInst()->AddSound(L"stage_Boss", L"sound\\BGM\\06 Pardoner's Dance.mp3", true);
	CSoundManager::getInst()->Play(L"stage_Boss");


	// 타일 로딩
	wstring path = CPathManager::getInst()->GetContentPath();
	path += L"tile\\Start.tile";
	LoadTile(path);

	// Player 추가
	CKaho* pPlayer = new CKaho;
	pPlayer->SetPos(fPoint(200, 200));
	pPlayer->RegisterPlayer();
	AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);

	//맵 생성
	CMap* map = new CMap;
	map->Load(L"Map_Start", L"texture\\map\\BackGround12.png");
	map->SetPos(fPoint(-200.f, 0.f));
	AddObject(map, GROUP_GAMEOBJ::MAP);




	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::MONSTER);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::MISSILE_PLAYER, GROUP_GAMEOBJ::MONSTER);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::TILE);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::MONSTER, GROUP_GAMEOBJ::TILE);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::HITBOX_PLAYER, GROUP_GAMEOBJ::MONSTER);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::BOSS, GROUP_GAMEOBJ::TILE);

	// Camera Look 지정
	CCameraManager::getInst()->SetLookAt(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
	CCameraManager::getInst()->SetTargetObj(pPlayer);
	//화면 전환시 검정색
	CCameraManager::getInst()->FadeOut(1.f);
	CCameraManager::getInst()->FadeIn(1.f);

	// 몬스터 배치
	CFennel* pFennel = CFennel::Create(Boss_PHASE::PHASE_1, fPoint(900.f, 300.f));
	AddObject(pFennel, GROUP_GAMEOBJ::BOSS);
}

void CScene_Boss::Exit()
{
	DeleteAll();

	CCollisionManager::getInst()->Reset();
}
