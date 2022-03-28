#include "framework.h"
#include "CScene_Start.h"

#include "CGameObject.h"
#include "CKaho.h"
#include "CMonster.h"
#include "CImp.h"
#include "CFennel.h"

#include "CMap.h"
#include "CBackGround.h"

#include "CSound.h"
#include "CD2DImage.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{	
}

void CScene_Start::update()
{
	CScene::update();

	if (KeyDown(VK_TAB))
	{
		ChangeScn(GROUP_SCENE::TOOL);
	}
	if (KeyDown('B'))
		ChangeScn(GROUP_SCENE::BOSS);
	
}

void CScene_Start::Enter()
{
	CSoundManager::getInst()->AddSound(L"stage1_BGM", L"sound\\BGM\\21 Hallowed_Ground.mp3", false,true	);
	CSoundManager::getInst()->Play(L"stage1_BGM");
	

	// 타일 로딩
	wstring path = CPathManager::getInst()->GetContentPath();
	path += L"tile\\Start.tile";
	LoadTile(path);

	// Player 추가
	CKaho* pPlayer = new CKaho;
	pPlayer->SetPos(fPoint(200, 200));
	pPlayer->RegisterPlayer();
	AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);
	
	
	//몬스터 추가
	//CMonster* pMonster = new CMonster;
	//pMonster->SetPos(fPoint(1100, 350));
	//AddObject(pMonster, GROUP_GAMEOBJ::MONSTER);

	//CMonster* pCloneMonster = pMonster->Clone();
	//pCloneMonster->SetPos(fPoint(500, 350));
	//AddObject(pCloneMonster, GROUP_GAMEOBJ::MONSTER);

	CImp* pImp = new CImp;
	pImp->SetPos(fPoint(700.f, 300.f));
	AddObject(pImp, GROUP_GAMEOBJ::MONSTER);

	//맵 생성
	CMap* map = new CMap;
	map->Load(L"Map_Start", L"texture\\map\\BackGround12.png");
	map->SetPos(fPoint(-100,-100));
	AddObject(map, GROUP_GAMEOBJ::MAP);

	


	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::MONSTER);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::MISSILE_PLAYER, GROUP_GAMEOBJ::MONSTER);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::TILE);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::MONSTER, GROUP_GAMEOBJ::TILE);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::HITBOX_PLAYER, GROUP_GAMEOBJ::MONSTER);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::BOSS, GROUP_GAMEOBJ::TILE);
	
	// Camera Look 지정
	CCameraManager::getInst()->SetLookAt(fPoint(WINSIZEX/2.f,WINSIZEY/2.f));
	/*CCameraManager::getInst()->SetTargetObj(pPlayer);*/
	//화면 전환시 검정색
	CCameraManager::getInst()->FadeOut(1.f);
	CCameraManager::getInst()->FadeIn(1.f);

	// 몬스터 배치
	CMonster* pMon = CMonster::Create(MON_TYPE::NORMAL, fPoint(300.f, 300.f));
	AddObject(pMon, GROUP_GAMEOBJ::MONSTER);
	CMonster* pMon2 = CMonster::Create(MON_TYPE::NORMAL, fPoint(500.f, 300.f));
	AddObject(pMon2, GROUP_GAMEOBJ::MONSTER);
	
	//CFennel* pFennel = CFennel::Create(Boss_PHASE::PHASE_1, fPoint(900.f, 300.f));
	//AddObject(pFennel, GROUP_GAMEOBJ::BOSS);
}

void CScene_Start::Exit()
{
	CSoundManager::getInst()->Stop(L"stage1_BGM");
	DeleteAll();
	CCollisionManager::getInst()->Reset();
}
