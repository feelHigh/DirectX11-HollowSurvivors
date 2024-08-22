#pragma once
#include "EditorUI.h"

class ComponentUI :
    public EditorUI
{
public:
    ComponentUI(COMPONENT_TYPE _Type);
    ~ComponentUI();

    void SetTargetObject(HHGameObject* _Object);
    HHGameObject* GetTargetObject() { return m_TargetObject; }

    COMPONENT_TYPE GetComponentUIType() { return m_Type; }

private:
    class HHGameObject*     m_TargetObject;

    const COMPONENT_TYPE    m_Type;

protected:
    void Title();

};
