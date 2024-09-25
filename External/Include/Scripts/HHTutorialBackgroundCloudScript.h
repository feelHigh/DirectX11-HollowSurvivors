#pragma once
#include <Engine/HHScript.h>

class HHTutorialBackgroundCloudScript :
    public HHScript
{
public:
    CLONE(HHTutorialBackgroundCloudScript);
    HHTutorialBackgroundCloudScript();
    ~HHTutorialBackgroundCloudScript();

    virtual void Begin() override;
    virtual void Tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

private:
    Ptr<HHTexture>  m_Texture;

};
