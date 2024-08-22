#pragma once
#include "HHRenderComponent.h"

class HHMeshRender :
    public HHRenderComponent
{
public:
    CLONE(HHMeshRender);
    HHMeshRender();
    ~HHMeshRender();

    virtual void FinalTick() override;
    virtual void Render() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

};
