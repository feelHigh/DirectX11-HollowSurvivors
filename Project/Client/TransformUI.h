#pragma once
#include "ComponentUI.h"

class TransformUI :
    public ComponentUI
{
public:
    TransformUI();
    ~TransformUI();

    virtual void Update() override;

};
