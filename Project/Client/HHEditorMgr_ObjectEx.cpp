#include "pch.h"
#include "HHEditorMgr.h"

#include "HHGameObjectEx.h"
#include <Engine/components.h>

#include "HHEditorCameraScript.h"
#include <Engine/HHRenderMgr.h>

void HHEditorMgr::CreateEditorObject()
{
	HHGameObject* pEditorCamera = new HHGameObjectEx;
	pEditorCamera->SetName(L"EditorCamera");
	pEditorCamera->AddComponent(new HHTransform);
	pEditorCamera->AddComponent(new HHCamera);
	pEditorCamera->AddComponent(new HHEditorCameraScript);

	pEditorCamera->Camera()->SetLayerAll();
	pEditorCamera->Camera()->SetLayer(31, false);
	pEditorCamera->Camera()->SetFar(100000.f);
	pEditorCamera->Camera()->SetProjectionType(ORTHOGRAPHIC);

	m_vecEditorObject.push_back(pEditorCamera);

	HHRenderMgr::GetInstance()->RegisterEditorCamera(pEditorCamera->Camera());
}
