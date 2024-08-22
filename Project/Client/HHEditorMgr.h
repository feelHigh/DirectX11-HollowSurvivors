#pragma once

#include <Engine/singleton.h>

class HHGameObject;
class EditorUI;

class HHEditorMgr :
    public HHSingleton<HHEditorMgr>
{
    SINGLE(HHEditorMgr);

public:
    void Initialize();
    void Tick();

    EditorUI* FindEditorUI(const string& Name);

    string wstring_to_string(const std::wstring& wstr);

private:
    vector<HHGameObject*>       m_vecEditorObject;
    map<string, EditorUI*>      m_mapUI;

    HANDLE                      m_hNotifyHandle;

    void ShortCut();

    void CreateEditorObject();
    void Progress_EditorObject();

    void Initialize_ImGui();
    void ObserveContent();
    void Tick_ImGui();
    void Progress_ImGui();
    
    void CreateEditorUI();

};
