#include "pch.h"
#include "MeshRenderUI.h"

#include <Engine/HHAssetMgr.h>
#include <Engine/HHMeshRender.h>
#include <Engine/HHMesh.h>
#include <Engine/HHMaterial.h>

#include "HHEditorMgr.h"
#include "ListUI.h"
#include "TreeUI.h"

MeshRenderUI::MeshRenderUI()
	: ComponentUI(COMPONENT_TYPE::MESHRENDER)
{
}

MeshRenderUI::~MeshRenderUI()
{
}

void MeshRenderUI::Update()
{
	Title();

	HHMeshRender* pMeshRender = GetTargetObject()->MeshRender();

	// 메쉬 정보
	Ptr<HHMesh> pMesh = pMeshRender->GetMesh();

	string MeshName;

	if (pMesh.Get())
		MeshName = string(pMesh->GetKey().begin(), pMesh->GetKey().end());

	ImGui::Text("Mesh");
	ImGui::SameLine(100);
	ImGui::SetNextItemWidth(150.f);
	ImGui::InputText("##MeshKey", (char*)MeshName.c_str(), ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);

	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ContentTree");
		if (payload)
		{
			TreeNode** ppNode = (TreeNode**)payload->Data;
			TreeNode* pNode = *ppNode;

			Ptr<HHAsset> pAsset = (HHAsset*)pNode->GetData();
			if (ASSET_TYPE::MESH == pAsset->GetAssetType())
			{
				pMeshRender->SetMesh((HHMesh*)pAsset.Get());
			}
		}

		ImGui::EndDragDropTarget();
	}

	ImGui::SameLine();
	if (ImGui::Button("##MeshBtn", ImVec2(18.f, 18.f)))
	{
		ListUI* pListUI = (ListUI*)HHEditorMgr::GetInstance()->FindEditorUI("List");

		vector<string> vecMeshNames;
		pListUI->SetName("Mesh");
		HHAssetMgr::GetInstance()->GetAssetNames(ASSET_TYPE::MESH, vecMeshNames);
		pListUI->AddList(vecMeshNames);
		pListUI->AddDelegate(this, (DELEGATE_1)&MeshRenderUI::SelectMesh);
		pListUI->SetActive(true);
	}

	// 머티리얼 정보
	Ptr<HHMaterial> pMtrl = pMeshRender->GetMaterial();

	string MtrlName;

	if (pMtrl.Get())
		MtrlName = string(pMtrl->GetKey().begin(), pMtrl->GetKey().end());

	ImGui::Text("Material");
	ImGui::SameLine(100);
	ImGui::SetNextItemWidth(150.f);
	ImGui::InputText("##MaterialKey", (char*)MtrlName.c_str(), ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);

	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ContentTree");
		if (payload)
		{
			TreeNode** ppNode = (TreeNode**)payload->Data;
			TreeNode* pNode = *ppNode;

			Ptr<HHAsset> pAsset = (HHAsset*)pNode->GetData();
			if (ASSET_TYPE::MATERIAL == pAsset->GetAssetType())
			{
				pMeshRender->SetMaterial((HHMaterial*)pAsset.Get());
			}
		}

		ImGui::EndDragDropTarget();
	}

	ImGui::SameLine();
	if (ImGui::Button("##MtrlBtn", ImVec2(18.f, 18.f)))
	{
		ListUI* pListUI = (ListUI*)HHEditorMgr::GetInstance()->FindEditorUI("List");

		vector<string> vecMtrlNames;
		pListUI->SetName("Material");
		HHAssetMgr::GetInstance()->GetAssetNames(ASSET_TYPE::MATERIAL, vecMtrlNames);
		pListUI->AddList(vecMtrlNames);
		pListUI->AddDelegate(this, (DELEGATE_1)&MeshRenderUI::SelectMaterial);
		pListUI->SetActive(true);
	}
}

void MeshRenderUI::SelectMesh(DWORD_PTR _ListUI)
{
	HHMeshRender* pMeshRender = GetTargetObject()->MeshRender();

	ListUI* pListUI = (ListUI*)_ListUI;
	string strName = pListUI->GetSelectName();

	if (strName == "None")
	{
		pMeshRender->SetMesh(nullptr);
		return;
	}

	wstring strAssetName = wstring(strName.begin(), strName.end());

	Ptr<HHMesh> pMesh = HHAssetMgr::GetInstance()->FindAsset<HHMesh>(strAssetName);

	assert(pMesh.Get());

	pMeshRender->SetMesh(pMesh);
}

void MeshRenderUI::SelectMaterial(DWORD_PTR _ListUI)
{
	HHMeshRender* pMeshRender = GetTargetObject()->MeshRender();

	ListUI* pListUI = (ListUI*)_ListUI;
	string strName = pListUI->GetSelectName();

	if ("None" == strName)
	{
		pMeshRender->SetMaterial(nullptr);
		return;
	}

	wstring strAssetName = wstring(strName.begin(), strName.end());

	Ptr<HHMaterial> pMtrl = HHAssetMgr::GetInstance()->FindAsset<HHMaterial>(strAssetName);

	assert(pMtrl.Get());

	pMeshRender->SetMaterial(pMtrl);
}
