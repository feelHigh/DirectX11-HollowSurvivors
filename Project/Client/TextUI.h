#pragma once
#include "ComponentUI.h"

class TextUI :
    public ComponentUI
{
public:
    TextUI();
    ~TextUI();

    virtual void Update() override;

    string ConvertWcharToString(const wchar_t* wstr);


};
