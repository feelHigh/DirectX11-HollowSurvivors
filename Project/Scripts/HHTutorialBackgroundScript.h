#pragma once
#include <Engine/HHScript.h>

class HHTutorialBackgroundScript:
    public HHScript
{
public:
    CLONE(HHTutorialBackgroundScript);
    HHTutorialBackgroundScript();
    ~HHTutorialBackgroundScript();

    virtual void Begin() override;
    virtual void Tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

private:
    Ptr<HHTexture>  m_Texture;

};
