#pragma once
#include "AssetUI.h"

class MeshUI :
    public AssetUI
{
public:
    MeshUI();
    ~MeshUI();

    virtual void Update() override;

};

