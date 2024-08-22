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
    Ptr<HHMaterial> GetDynamicMaterial();       // ���� ���� ���� �� ��ȯ

    void SaveDataToFile(FILE* _File);
    void LoadDataFromFile(FILE* _File);

private:
    Ptr<HHMesh>             m_Mesh;             // ���� ��� ���� �Ž�

    Ptr<HHMaterial>         m_Material;         // ���� ��� ���� ����
    Ptr<HHMaterial>         m_SharedMaterial;   // ���� ����(Master)
    Ptr<HHMaterial>         m_DynamicMaterial;  // �ӽ� ����

};
