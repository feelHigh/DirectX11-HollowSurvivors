#pragma once
#include "EditorUI.h"

class Content :
    public EditorUI
{
public:
    Content();
    ~Content();

    virtual void Initialize() override;
    virtual void Update() override;

    // Content ������ �ִ� ���ҽ�(����) ���� Ȯ�� �� �ε�
    void Reload();

private:
    class TreeUI*   m_Tree;
    vector<wstring> m_vecAssetPath; // Content ������ �ִ� ���� ���

    void RenewContent();

    void AssetClicked(DWORD_PTR _Param);
    void PopupMenu(DWORD_PTR _Param);

    void FindAssetName(const wstring& _FolderPath, const wstring& _Filter);
    void LoadAsset(const path& _Path);

};
