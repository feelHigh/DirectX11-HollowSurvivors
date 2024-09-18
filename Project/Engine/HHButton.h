#pragma once
#include "HHComponent.h"

class HHButton :
    public HHComponent
{
public:
    CLONE(HHButton);
	HHButton();
	~HHButton();

    virtual void Begin() override;
    virtual void Tick() override;
    virtual void FinalTick() override;

    void SetButtonType(BUTTON_TYPE _Type) { mType = _Type; }
    BUTTON_TYPE GetButtonType() { return mType; }

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

private:
    BUTTON_TYPE mType;

};
