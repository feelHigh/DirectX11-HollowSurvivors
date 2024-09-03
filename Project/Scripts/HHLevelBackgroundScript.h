#pragma once
#include <Engine/HHScript.h>

class HHLevelBackgroundScript :
    public HHScript
{
public:
    CLONE(HHLevelBackgroundScript);
    HHLevelBackgroundScript();
    ~HHLevelBackgroundScript();

    virtual void Begin() override;
    virtual void Tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

private:
    Ptr<HHTexture>  m_Texture;

};
