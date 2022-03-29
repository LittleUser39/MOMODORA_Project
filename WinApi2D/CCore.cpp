#include "framework.h"
#include "CCore.h"
#include "CGameObject.h"
#include "CTexture.h"

CCore::CCore()
{
	M_bDebug = false;
}

CCore::~CCore()
{

}

void CCore::update()
{
	// ���� update���� �߰��� �̺�Ʈ�� ������ �ʱ⿡ �Ѳ����� ó��
	CEventManager::getInst()->update();

	CTimeManager::getInst()->update();
	CKeyManager::getInst()->update();
	CSoundManager::getInst()->update();

	CSceneManager::getInst()->update();
	CCollisionManager::getInst()->update();
	CCameraManager::getInst()->update();
	CUIManager::getInst()->update();
	if (KeyDown(VK_F11))
		M_bDebug = !M_bDebug;
}

void CCore::render()
{
	CRenderManager::getInst()->GetRenderTarget()->BeginDraw();

	CRenderManager::getInst()->RenderFillRectangle(-1, -1, WINSIZEX + 1, WINSIZEY + 1, RGB(255, 255, 255));

	CSceneManager::getInst()->render();
	CCameraManager::getInst()->render();

	// ������ ��ܿ� FPS ǥ��
	WCHAR strFPS[6];
	swprintf_s(strFPS, L"%5d", CTimeManager::getInst()->GetFPS());
	CRenderManager::getInst()->RenderText(strFPS, WINSIZEX - 50, 10, WINSIZEX, 50, 12, RGB(255, 255, 255));

	CRenderManager::getInst()->GetRenderTarget()->EndDraw();
}

void CCore::init()
{
	

	CPathManager::getInst()->init();
	CTimeManager::getInst()->init();
	CKeyManager::getInst()->init();
	CSoundManager::getInst()->init();
	CRenderManager::getInst()->init();

	CCameraManager::getInst()->init();
	CSceneManager::getInst()->init();
	CCollisionManager::getInst()->init();
}
