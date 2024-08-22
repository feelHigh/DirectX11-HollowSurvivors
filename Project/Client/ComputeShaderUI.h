#pragma once
#include "AssetUI.h"

class ComputeShaderUI :
    public AssetUI
{
public:
    ComputeShaderUI();
    ~ComputeShaderUI();

    virtual void Update() override;

};
