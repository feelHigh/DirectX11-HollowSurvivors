#pragma once
#include "AssetUI.h"

class MaterialUI
    : public AssetUI
{
public:
    MaterialUI();
    ~MaterialUI();

    virtual void Update() override;

    void ChangeTexture(DWORD_PTR Param);

private:
    TEXTURE_PARAM   m_SelectTexParam;

    void SelectShader(DWORD_PTR _ListUI);
    void SaveMaterialToFile();
    void ShaderParameter();

};
