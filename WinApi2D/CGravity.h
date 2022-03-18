#pragma once
class CGameObject;

class CGravity
{
    friend class CGameObject;
public:
    CGravity();
    ~CGravity();

    virtual void finalupdate();

    void SetGround(bool _b);
private:
    CGameObject* m_pOwner;
    bool     m_bGround;

  
};