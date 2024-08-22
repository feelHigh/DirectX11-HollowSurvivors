#pragma once
#include "EditorUI.h"

class AssetUI :
    public EditorUI
{
public:
    AssetUI(ASSET_TYPE _Type);
    ~AssetUI();

    void SetAsset(Ptr<HHAsset> _Asset);
    Ptr<HHAsset> GetAsset() { return m_Asset; }

private:
    Ptr<HHAsset>         m_Asset;
    const ASSET_TYPE    m_Type;

protected:
    void Title();
    void OutputAssetName();

};
