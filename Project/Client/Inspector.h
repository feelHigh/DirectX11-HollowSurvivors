#pragma once
#include "EditorUI.h"

#include<Engine/assets.h>

class Inspector :
    public EditorUI
{
public:
    Inspector();
    ~Inspector();

    virtual void Initialize() override;
    virtual void Update() override;

    void SetTargetObject(HHGameObject* _Object);
    void SetTargetAsset(Ptr<HHAsset> _Asset);

    HHGameObject* GetTargetObject() { return m_TargetObject; }
    Ptr<HHAsset> GetTargetAsset() { return m_TargetAsset; }
     
private:
    class HHGameObject*         m_TargetObject;
    class ComponentUI*          m_arrComponentUI[(UINT)COMPONENT_TYPE::END];
    vector<class ScriptUI*>     m_vecScriptUI;

    Ptr<HHAsset>                m_TargetAsset;
    class AssetUI*              m_arrAssetUI[(UINT)ASSET_TYPE::END];

    void CreateComponentUI();
    void CreateScriptUI(UINT _Count);
    void CreateAssetUI();

};
