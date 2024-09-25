#pragma once
#include <Engine/HHScript.h>

class HHTutorialMapScript :
    public HHScript
{
public:
    CLONE(HHTutorialMapScript);
    HHTutorialMapScript();
    ~HHTutorialMapScript();

    virtual void Begin() override;
    virtual void Tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

private:
    Ptr<HHTexture>  m_Texture;

};
