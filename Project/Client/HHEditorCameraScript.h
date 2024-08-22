#pragma once
#include <Engine/HHScript.h>

class HHEditorCameraScript :
    public HHScript
{
public:
    CLONE(HHEditorCameraScript);
    HHEditorCameraScript();
    ~HHEditorCameraScript();

    virtual void Tick() override;

    virtual void SaveToFile(FILE* _File) override {}
    virtual void LoadFromFile(FILE* _File)override {}

private:
    float   m_Speed;

    void OrthographicMovement();
    void PerspectiveMovement();

};
