// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#pragma comment(lib, "Msimg32.lib")

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string>
#include <math.h>
#include <assert.h>

// STL
#include <vector>
#include <map>
#include <list>

using namespace std;

// Util
#include "SingleTon.h"
#include "struct.h"
#include "Logger.h"


//========================================
//## 게임 그룹						##
//========================================

enum class GROUP_GAMEOBJ
{
	DEFAULT,
	BACKGROUND,
	MAP,
	TILE,
	GROUND,
	MONSTER,
	BOSS,
	MISSILE_MONSTER,
	MISSILE_PLAYER,
	PLAYER,
	HITBOX_MONSTER,
	HITBOX_PLAYER,
	UI,		// UI는 모든 게임오브젝트 중 최상단 Layer에 위치
	SIZE,
};

enum class GROUP_SCENE
{
	TOOL,
	TITLE,
	SELECT,
	START,
	STAGE_01,
	BOSS,

	SIZE,
};

enum class GROUP_TILE
{
	NONE,		//없음
	GROUND,		//땅
	PLATFORM,	//아래에서 뚫고감 위에서 아래키 누를시 내려감
	WALL,		//벽

	SIZE,
};

enum class MON_STATE
{
	IDLE,
	PATROL,
	TRACE,
	ATT,
	RUN,
	DEAD,

	SIZE,
};

enum class Boss_Pattern
{
	IDLE,
	DASH,
	BACK,
	SWORDATTACK,
	LIGTHNING,
	SWORDSTRIKE,
};
//========================================
//## 이벤트 타입					##
//========================================

enum class TYPE_EVENT
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	CHANGE_SCENE,
	CHANGE_AI_STATE,

	SIZE,
};

// Core & Manager
#include "CCore.h"
#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CSceneManager.h"
#include "CPathManager.h"
#include "CCollisionManager.h"
#include "CEventManager.h"
#include "CResourceManager.h"
#include "CCameraManager.h"
#include "CUIManager.h"
#include "CSoundManager.h"
#include "CRenderManager.h"
#include "CRigidBody.h"
//========================================
//##			디파인문				##
//========================================

#define WINSTARTX   100
#define WINSTARTY   100
#define WINSIZEX	1000
#define	WINSIZEY	720
#define WINSTYLE	WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX

#define DT				CTimeManager::getInst()->GetDT()
#define fDT				CTimeManager::getInst()->GetfDT()

#define Key(key)		CKeyManager::getInst()->GetButton(key)		//이전과 현재키가 같이 눌림
#define KeyUp(key)		CKeyManager::getInst()->GetButtonUP(key)	//이전은 눌리고 현재는 안눌림
#define KeyDown(key)	CKeyManager::getInst()->GetButtonDOWN(key)  //이전은 안눌리고 현재 눌림

#define MousePos()		CKeyManager::getInst()->GetMousePos()

#define CreateObj(pObj, group)	CEventManager::getInst()->EventCreateObject(pObj, group)
#define DeleteObj(pObj)			CEventManager::getInst()->EventDeleteObject(pObj)
#define ChangeScn(scene)		CEventManager::getInst()->EventChangeScene(scene)
#define ChangeAIState(ai, state)	CEventManager::getInst()->EventChangeAIState(ai, state)
#define ChangeBossAIState(ai, state)	CEventManager::getInst()->EventChangeBossAIState(ai, state)
//========================================
//## 전역변수(인스턴스, 윈도우 핸들)	##
//========================================

extern HINSTANCE hInst;
extern HWND hWnd;
