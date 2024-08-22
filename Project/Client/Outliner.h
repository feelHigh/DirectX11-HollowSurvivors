#pragma once
#include "EditorUI.h"

class Outliner :
    public EditorUI
{
public:
    Outliner();
    ~Outliner();

    virtual void Update() override;

private:
    class TreeUI* m_Tree;

    void RenewLevel();
    void AddGameObject(class TreeNode* pNode, class HHGameObject* _Object);

    void GameObjectAddChild(DWORD_PTR _Param1, DWORD_PTR _Param2);
    void DroppedFromOuter(DWORD_PTR _OuterData, DWORD_PTR _DropNode);

    void GameObjectClicked(DWORD_PTR _Param);

};
