#pragma once
#include <Engine/HHScript.h>

class HHCameraMoveScript :
    public HHScript
{
public:
    CLONE(HHCameraMoveScript);
    HHCameraMoveScript();
    ~HHCameraMoveScript();

    virtual void Tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

private:
    float   m_CamSpeed;

    void OrthographicMovement();
    void PerspectiveMovement();
};
