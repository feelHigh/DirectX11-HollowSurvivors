#pragma once
#include "HHComponent.h"

class HHRenderComponent :
    public HHComponent
{
public:
    CLONE_DISABLE(HHRenderComponent);
    HHRenderComponent(COMPONENT_TYPE _Type);
    HHRenderComponent(const HHRenderComponent& _Origin);
    ~HHRenderComponent();

    virtual void FinalTick() = 0;
    virtual void Render() = 0;

    void SetMesh(Ptr<HHMesh> _Mesh) { m_Mesh = _Mesh; }
    Ptr<HHMesh> GetMesh() { return m_Mesh; }

    void SetMaterial(Ptr<HHMaterial> _Material);
    Ptr<HHMaterial> GetMaterial() { return m_Material; }
    Ptr<HHMaterial> GetSharedMaterial();
    Ptr<HHMaterial> GetDynamicMaterial();       // 동적 재질 생성 및 반환

    void SaveDataToFile(FILE* _File);
    void LoadDataFromFile(FILE* _File);

private:
    Ptr<HHMesh>             m_Mesh;             // 현재 사용 중인 매쉬

    Ptr<HHMaterial>         m_Material;         // 현재 사용 중인 재질
    Ptr<HHMaterial>         m_SharedMaterial;   // 공유 재질(Master)
    Ptr<HHMaterial>         m_DynamicMaterial;  // 임시 재질

};
