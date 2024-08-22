#include "pch.h"
#include "HHEditorMgr.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

#include <Engine/HHEngine.h>
#include <Engine/HHDevice.h>
#include <Engine/HHPathMgr.h>
#include <Engine/HHKeyMgr.h>
#include <Engine/HHRenderMgr.h>
#include <Engine/components.h>

#include "HHGameObjectEx.h"
#include "HHEditorCameraScript.h"

#include "EditorUI.h"

HHEditorMgr::HHEditorMgr()
    : m_hNotifyHandle(nullptr)
{
}

HHEditorMgr::~HHEditorMgr()
{
	Delete_Vec(m_vecEditorObject);
    Delete_Map(m_mapUI);

	// ImGui Cleanup
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void HHEditorMgr::Initialize()
{
    CreateEditorObject();

	Initialize_ImGui();

    // Content 폴더를 감시하는 커널 오브젝트 생성
    wstring ContentPath = HHPathMgr::GetInstance()->GetContentPath();
    m_hNotifyHandle = FindFirstChangeNotification(ContentPath.c_str(), true
                                                , FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME
                                                | FILE_ACTION_ADDED | FILE_ACTION_REMOVED);
}

void HHEditorMgr::Tick()
{
    ShortCut();

    Progress_EditorObject();

	Progress_ImGui();

    ObserveContent();
}

void HHEditorMgr::ShortCut()
{
    if (KEY_TAP(KEY::I))
    {
        EditorUI* pUI = FindEditorUI("Inspector");

        if (pUI->IsActive())
            pUI->SetActive(false);
        else
            pUI->SetActive(true);
    }
}

void HHEditorMgr::Progress_EditorObject()
{
    for (size_t i = 0; i < m_vecEditorObject.size(); ++i)
    {
        m_vecEditorObject[i]->Tick();
    }

    for (size_t i = 0; i < m_vecEditorObject.size(); ++i)
    {
        m_vecEditorObject[i]->FinalTick();
    }
}

void HHEditorMgr::Tick_ImGui()
{
    ImGui::ShowDemoWindow();

    for (const auto& pair : m_mapUI)
    {
        pair.second->Tick();
    }
}
