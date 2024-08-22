#include "pch.h"
#include "SpriteEditorDetail.h"

#include "HHEditorMgr.h"
#include "ListUI.h"
#include "TreeUI.h"

#include "SpriteEditorAtlasView.h"

#include <Engine/HHAssetMgr.h>

SpriteEditorDetail::SpriteEditorDetail()
{
}

SpriteEditorDetail::~SpriteEditorDetail()
{
}

void SpriteEditorDetail::Initialize()
{
}

void SpriteEditorDetail::Update()
{
	Atlas();

	AtlasInfo();
}

void SpriteEditorDetail::SetAtlasTex(Ptr<HHTexture> _Tex)
{
	m_AtlasTex = _Tex;
	GetAtlasView()->SetAtlasTex(m_AtlasTex);
}

void SpriteEditorDetail::Atlas()
{
	string TexName;

	if (nullptr != m_AtlasTex)
		TexName = string(m_AtlasTex->GetKey().begin(), m_AtlasTex->GetKey().end());

	ImGui::Text("Atlas Texture");
	ImGui::SameLine(120);
	ImGui::SetNextItemWidth(150.f);
	ImGui::InputText("##AtlasTex", (char*)TexName.c_str(), ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);

	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ContentTree");
		if (payload)
		{
			TreeNode** ppNode = (TreeNode**)payload->Data;
			TreeNode* pNode = *ppNode;

			Ptr<HHAsset> pAsset = (HHAsset*)pNode->GetData();
			if (ASSET_TYPE::TEXTURE == pAsset->GetAssetType())
			{
				SetAtlasTex((HHTexture*)pAsset.Get());
			}
		}

		ImGui::EndDragDropTarget();
	}

	ImGui::SameLine();
	if (ImGui::Button("##AtlasTexBtn", ImVec2(18.f, 18.f)))
	{
		ListUI* pListUI = (ListUI*)HHEditorMgr::GetInstance()->FindEditorUI("List");
		pListUI->SetName("Texture");
		vector<string> vecTexNames;
		HHAssetMgr::GetInstance()->GetAssetNames(ASSET_TYPE::TEXTURE, vecTexNames);
		pListUI->AddList(vecTexNames);
		pListUI->AddDelegate(this, (DELEGATE_1)&SpriteEditorDetail::SelectTexture);
		pListUI->SetActive(true);
	}
}

void SpriteEditorDetail::AtlasInfo()
{
	// ÇØ»óµµ
	UINT width = 0;
	UINT height = 0;

	if (nullptr != m_AtlasTex)
	{
		width = m_AtlasTex->Width();
		height = m_AtlasTex->Height();
	}

	char buff[50] = {};
	sprintf_s(buff, "%d", width);

	ImGui::Text("Width");
	ImGui::SameLine(100);
	ImGui::InputText("##TextureWidth", buff, 50, ImGuiInputTextFlags_ReadOnly);

	sprintf_s(buff, "%d", height);
	ImGui::Text("Height");
	ImGui::SameLine(100);
	ImGui::InputText("##TextureHeight", buff, 50, ImGuiInputTextFlags_ReadOnly);
}

void SpriteEditorDetail::SelectTexture(DWORD_PTR _ListUI)
{
	ListUI* pListUI = (ListUI*)_ListUI;
	string strName = pListUI->GetSelectName();

	if (strName == "None")
	{
		m_AtlasTex = nullptr;
		return;
	}

	wstring strAssetName = wstring(strName.begin(), strName.end());

	Ptr<HHTexture> pTex = HHAssetMgr::GetInstance()->FindAsset<HHTexture>(strAssetName);

	assert(pTex.Get());

	SetAtlasTex(pTex);
}
