#pragma once
#include <Engine/HHScript.h>

enum class PLAYER_STATE
{
    IDLE,
    MOVE,
    DASH,
    ATTACK_MELEE,
    ATTACK_SPELL,
    DEAD,
    NONE,
};

class HHPlayerScript :
    public HHScript
{
public:
    CLONE(HHPlayerScript);
    HHPlayerScript();
    ~HHPlayerScript();

    virtual void Begin() override;
    virtual void Tick() override;

    virtual void BeginOverlap(HHCollider2D* _OwnCollider, HHGameObject* _OtherObject, HHCollider2D* _OtherCollider) override;
    virtual void Overlap(HHCollider2D* _OwnCollider, HHGameObject* _OtherObject, HHCollider2D* _OtherCollider) override;
    virtual void EndOverlap(HHCollider2D* _OwnCollider, HHGameObject* _OtherObject, HHCollider2D* _OtherCollider) override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

private:
    void Idle();
    void Move();
    void Dash();
    void Attack_Melee();
    void Attack_Spell();
    void Dead();

    void Idle_Animation();
    void Move_Animation();
    void Dash_Animation();
    void Attack_Melee_Animation();
    void Attack_Spell_Animation();
    void Dead_Animation();

    void ResetCombo();

private:
    // Base Status
    DIR                     m_eDir;
    PLAYER_STATE            m_eState;

    UINT                    m_uHP;
    UINT                    m_uMP;
    UINT                    m_uProgress;

    float                   m_fSpeed;

    // Flipbook
    vector<Ptr<HHFlipbook>> m_vFlipbooks;
    int                     m_iFPS;

    // Melee Combo
    int                     m_iCombo;
    float                   m_fComboTimer;   // Timer to track combo duration
    bool                    m_bComboActive;  // Whether a combo is currently active

};
