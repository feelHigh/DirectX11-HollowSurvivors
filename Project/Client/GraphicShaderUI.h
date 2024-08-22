#pragma once
#include "AssetUI.h"

class GraphicShaderUI :
    public AssetUI
{
public:
    GraphicShaderUI();
    ~GraphicShaderUI();

    virtual void Update() override;

};
