#pragma once
#include "ComponentUI.h"

class TilemapUI :
    public ComponentUI
{
public:
    TilemapUI();
    ~TilemapUI();

private:
    virtual void Update() override;

};
