#pragma once
#include "AssetUI.h"

class FSMUI :
    public AssetUI
{
public:
    FSMUI();
    ~FSMUI();

    virtual void Update() override;

};
