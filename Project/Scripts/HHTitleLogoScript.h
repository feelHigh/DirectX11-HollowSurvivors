#pragma once
#include <Engine/HHScript.h>

class HHTitleLogoScript :
    public HHScript
{
public:
    CLONE(HHTitleLogoScript);
    HHTitleLogoScript();
    ~HHTitleLogoScript();

    virtual void Begin() override;
    virtual void Tick() override;

    virtual void BeginOverlap(HHCollider2D* _OwnCollider, HHGameObject* _OtherObject, HHCollider2D* _OtherCollider) override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

private:
    Ptr<HHTexture>  m_Texture;

};
