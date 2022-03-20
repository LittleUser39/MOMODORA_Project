#pragma once
class CGameObject;

class CGravity
{
    friend class CGameObject;
private:
    CGameObject*    m_pOwner;
    bool            m_bGround;
    
public:
    CGravity();
    ~CGravity();

    virtual void finalupdate();

    void SetGround(bool _b);
  
};