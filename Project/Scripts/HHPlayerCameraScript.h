#pragma once
#include <Engine/HHScript.h>

class HHPlayerCameraScript :
    public HHScript
{
public:
    CLONE(HHPlayerCameraScript);
    HHPlayerCameraScript();
    ~HHPlayerCameraScript();

    virtual void Tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

private:
    float   m_CamSpeed;

    void PerspectiveMovement();
};
