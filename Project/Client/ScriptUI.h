#pragma once
#include "ComponentUI.h"

#include <Engine/HHScript.h>

class ScriptUI :
    public ComponentUI
{
public:
    ScriptUI();
    ~ScriptUI();

    virtual void Update() override;

    void SetTargetScript(HHScript* _Script);
    HHScript* GetTargetScript() { return m_Script; }

private:
    class HHScript* m_Script;

    UINT            m_UIHeight;

    Ptr<HHPrefab>*  m_SelectedPrefab;

    void SelectPrefab(DWORD_PTR _ListUI);

};
