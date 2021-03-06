#include "framework.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CGameObject.h"
#include "CTexture.h"
#include "CD2DImage.h"
CAnimation::CAnimation()
{
    m_strName = L"";
    m_pAnimator = nullptr;
    m_pImg = nullptr;
    m_iCurFrm = 0;
    m_fAccTime = 0;
    m_bFinish = false;
}

CAnimation::~CAnimation()
{
}

CAnimation::CAnimation(const CAnimation& pOther)
{
    m_strName = pOther.m_strName;
    for (int i = 0; i < pOther.m_vecFrm.size(); i++)
    {
        m_vecFrm.push_back(pOther.m_vecFrm[i]);
    }
    m_iCurFrm = pOther.m_iCurFrm;
    m_fAccTime = pOther.m_fAccTime;
    m_bReverse = pOther.m_bReverse;

    m_pAnimator = nullptr;
    m_pImg = pOther.m_pImg;
}

void CAnimation::SetName(const wstring& strName)
{
    m_strName = strName;
}

const wstring& CAnimation::GetName()
{
    return m_strName;
}

void CAnimation::SetLoop(bool isLoop)
{
    m_Loop = isLoop;
}

bool CAnimation::GetAniFinish()
{
    return m_bFinish;
}

void CAnimation::SetFrame(int frmIndex)
{
    m_iCurFrm = frmIndex;
}

tAniFrm& CAnimation::GetFrame(int frmIndex)
{
    return m_vecFrm[frmIndex];
}

void CAnimation::update()
{
    m_fAccTime += fDT;

    if (m_fAccTime >= m_vecFrm[m_iCurFrm].fDuration)
    {
        // 축적 시간 -> fDuration 만큼 다시 빼줌 -> 0으로 초기화보다는 정확
        m_fAccTime -= m_vecFrm[m_iCurFrm].fDuration;

        m_iCurFrm++;

        if (m_Loop)
        {
            // 애니메이션에 끝에 도달했으면 처음 프레임으로 돌아감
            m_iCurFrm %= m_vecFrm.size();
        }
        else
        {
            if (m_iCurFrm == m_vecFrm.size())
            {
                m_iCurFrm = (int)m_vecFrm.size() - 1;
                m_bFinish = true;
            }
        }
    }
}

void CAnimation::render()
{
    CGameObject* pObj = m_pAnimator->GetObj();
    fPoint fptPos = pObj->GetPos();
    fPoint fptScale = pObj->GetScale();
    tAniFrm frm = m_vecFrm[m_iCurFrm];

    fptPos = fptPos + frm.fptOffset;
    fptPos = CCameraManager::getInst()->GetRenderPos(fptPos);

	//todo 이곳에서 수정 애니메이션 그자체의 크기를 가져와서 그리도록
    if (m_bReverse)
    {
        CRenderManager::getInst()->RenderRevFrame(
            m_pImg,
            fptPos.x - fptScale.x / 2.f,
            fptPos.y - fptScale.y / 2.f,
            fptPos.x + fptScale.x / 2.f,
            fptPos.y + fptScale.y / 2.f,
            frm.fptLT.x,
            frm.fptLT.y,
            frm.fptLT.x + frm.fptSlice.x,
            frm.fptLT.y + frm.fptSlice.y
        );
    }
    else
    {
        CRenderManager::getInst()->RenderFrame(
            m_pImg,
            fptPos.x - fptScale.x / 2.f,
            fptPos.y - fptScale.y / 2.f,
            fptPos.x + fptScale.x / 2.f,
            fptPos.y + fptScale.y / 2.f,
            frm.fptLT.x,
            frm.fptLT.y,
            frm.fptLT.x + frm.fptSlice.x,
            frm.fptLT.y + frm.fptSlice.y
        );
    }

}

void CAnimation::Create(CD2DImage* img,     // 애니메이션의 이미지
                        fPoint lt,          // 애니메이션 시작 프레임의 좌상단 좌표
                        fPoint slice,       // 애니메이션 프레임의 크기
                        fPoint step,        // 애니메이션 프레임의 반복 위치
                        float duration,     // 애니메이션 프레임 지속시간
                        UINT frmCount)      // 애니메이션 프레임 갯수
{
    m_pImg = img;

    tAniFrm frm = {};
    for (UINT i = 0; i < frmCount; i++)
    {
        frm.fDuration = duration;
        frm.fptSlice = slice;
        frm.fptLT = lt + step * i;

        m_vecFrm.push_back(frm);
    }
}
