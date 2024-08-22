#pragma once
#include <Engine/HHGameObject.h>

class HHGameObjectEx :
    public HHGameObject
{
public:
    CLONE(HHGameObjectEx);

    virtual void FinalTick() override;

};
