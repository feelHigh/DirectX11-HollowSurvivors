#pragma once
#include "ComponentUI.h"

class FlipbookRenUI :
    public ComponentUI
{
public:
    FlipbookRenUI();
    ~FlipbookRenUI();

private:
    virtual void Update() override;

};
