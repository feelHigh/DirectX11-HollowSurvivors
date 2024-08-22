#pragma once
#include "ComponentUI.h"

class Light2DUI :
    public ComponentUI
{
public:
    Light2DUI();
    ~Light2DUI();

private:
    virtual void Update() override;

    void SelectLightType(LIGHT_TYPE SelectLight);

};
