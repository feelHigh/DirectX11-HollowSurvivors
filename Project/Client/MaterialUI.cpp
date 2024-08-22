#include "pch.h"
#include "MaterialUI.h"

#include "ListUI.h"
#include "TreeUI.h"
#include "HHEditorMgr.h"
#include "ParamUI.h"

#include <Engine/HHAssetMgr.h>

MaterialUI::MaterialUI()
	: AssetUI(ASSET_TYPE::MATERIAL)
{
}

MaterialUI::~MaterialUI()
{
}


void MaterialUI::Update()
{
	Title();

	// ���� �̸�
	OutputAssetName();

	Ptr<HHMaterial> pMtrl = (HHMaterial*)GetAsset().Get();

	// �����ϴ� ���̴� �̸�
	Ptr<HHGraphicShader> pShader = pMtrl->GetShader();
	string Name;

	if (nullptr == pShader)
		Name = "None";
	else
		Name = string(pShader->GetKey().begin(), pShader->GetKey().end());

	// ���̴� �̸�
	ImGui::Text("Shader");
	ImGui::SameLine(100);
	ImGui::InputText("##ShaderName", (char*)Name.c_str(), Name.length(), ImGuiInputTextFlags_ReadOnly);

	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ContentTree");
		if (payload)
		{
			TreeNode** ppNode = (TreeNode**)payload->Data;
			TreeNode* pNode = *ppNode;

			Ptr<HHAsset> pAsset = (HHAsset*)pNode->GetData();
			if (ASSET_TYPE::GRAPHIC_SHADER == pAsset->GetAssetType())
			{
				pMtrl->SetShader((HHGraphicShader*)pAsset.Get());
				SaveMaterialToFile();
			}
		}

		ImGui::EndDragDropTarget();
	}

	ImGui::SameLine();
	if (ImGui::Button("##ShaderBtn", ImVec2(18.f, 18.f)))
	{
		ListUI* pListUI = (ListUI*)HHEditorMgr::GetInstance()->FindEditorUI("List");
		pListUI->SetName("GraphicShader");
		vector<string> vecMeshNames;
		HHAssetMgr::GetInstance()->GetAssetNames(ASSET_TYPE::GRAPHIC_SHADER, vecMeshNames);
		pListUI->AddList(vecMeshNames);
		pListUI->AddDelegate(this, (DELEGATE_1)&MaterialUI::SelectShader);
		pListUI->SetActive(true);
	}

	ImGui::Text("");
	ImGui::Text("");
	ImGui::Text("Shader Parameter");

	// Shader Parameter
	ShaderParameter();
}

void MaterialUI::ChangeTexture(DWORD_PTR Param)
{
	// �ؽ��� �Ķ���͸� �Է¹��� ����
	Ptr<HHMaterial> pMtrl = (HHMaterial*)GetAsset().Get();

	// ���������� ������ �׸��� �������� ListUI �� ���ؼ� �˾Ƴ�
	ListUI* pListUI = (ListUI*)Param;
	string strName = pListUI->GetSelectName();

	if ("None" == strName)
	{
		pMtrl->SetTextureParam(m_SelectTexParam, nullptr);
		SaveMaterialToFile();
		return;
	}

	wstring strAssetName = wstring(strName.begin(), strName.end());

	Ptr<HHTexture> pTex = HHAssetMgr::GetInstance()->FindAsset<HHTexture>(strAssetName);

	assert(pMtrl.Get());

	pMtrl->SetTextureParam(m_SelectTexParam, pTex);
	SaveMaterialToFile();
}

void MaterialUI::SelectShader(DWORD_PTR _ListUI)
{
	Ptr<HHMaterial> pMtrl = (HHMaterial*)GetAsset().Get();

	ListUI* pListUI = (ListUI*)_ListUI;
	string strName = pListUI->GetSelectName();

	if ("None" == strName)
	{
		pMtrl->SetShader(nullptr);
		SaveMaterialToFile();
		return;
	}

	wstring strAssetName = wstring(strName.begin(), strName.end());

	Ptr<HHGraphicShader> pShader = HHAssetMgr::GetInstance()->FindAsset<HHGraphicShader>(strAssetName);

	assert(pShader.Get());

	pMtrl->SetShader(pShader);
	SaveMaterialToFile();
}

void MaterialUI::SaveMaterialToFile()
{
	Ptr<HHMaterial> pMtrl = (HHMaterial*)GetAsset().Get();

	if (!pMtrl->IsEngineAsset())
	{
		if (FAILED(pMtrl->Save(pMtrl->GetRelativePath())))
		{
			int a = 0;
		}
	}
}

void MaterialUI::ShaderParameter()
{
	Ptr<HHMaterial> pMtrl = (HHMaterial*)GetAsset().Get();
	Ptr<HHGraphicShader> pShader = pMtrl->GetShader();

	if (nullptr == pShader)
		return;

	// Shader �� �䱸�ϴ� �Ķ���� ����� �����´�.
	const vector<tScalarParam>& vecScalarParam = pShader->GetScalarParam();
	const vector<tTexParam>& vecTexParam = pShader->GetTexParam();

	// Scalar �Ķ���� ����
	for (size_t i = 0; i < vecScalarParam.size(); ++i)
	{
		switch (vecScalarParam[i].ParamType)
		{
		case INT_0:
		case INT_1:
		case INT_2:
		case INT_3:
		{
			int data = *((int*)pMtrl->GetScalarParam(vecScalarParam[i].ParamType));
			if (ParamUI::DragInt(&data, 1, vecScalarParam[i].strDesc))
			{
				pMtrl->SetScalarParam(vecScalarParam[i].ParamType, data);
				SaveMaterialToFile();
			}
		}

		break;
		case FLOAT_0:
		case FLOAT_1:
		case FLOAT_2:
		case FLOAT_3:
		{
			float data = *((float*)pMtrl->GetScalarParam(vecScalarParam[i].ParamType));
			if (ParamUI::DragFloat(&data, 0.1f, vecScalarParam[i].strDesc))
			{
				pMtrl->SetScalarParam(vecScalarParam[i].ParamType, data);
				SaveMaterialToFile();
			}
		}
		break;
		case VEC2_0:
		case VEC2_1:
		case VEC2_2:
		case VEC2_3:
		{
			Vec2 data = *((Vec2*)pMtrl->GetScalarParam(vecScalarParam[i].ParamType));
			if (ParamUI::DragVec2(&data, 0.1f, vecScalarParam[i].strDesc))
			{
				pMtrl->SetScalarParam(vecScalarParam[i].ParamType, data);
				SaveMaterialToFile();
			}
		}
		break;
		case VEC4_0:
		case VEC4_1:
		case VEC4_2:
		case VEC4_3:
		{
			Vec4 data = *((Vec4*)pMtrl->GetScalarParam(vecScalarParam[i].ParamType));
			if (ParamUI::DragVec4(&data, 0.1f, vecScalarParam[i].strDesc))
			{
				pMtrl->SetScalarParam(vecScalarParam[i].ParamType, data);
				SaveMaterialToFile();
			}
		}
		break;
		case MAT_0:
		case MAT_1:
		case MAT_2:
		case MAT_3:
		{
			Matrix data = *((Matrix*)pMtrl->GetScalarParam(vecScalarParam[i].ParamType));
			SaveMaterialToFile();

		}
		break;
		}
	}

	// Texture �Ķ���� ����

	for (size_t i = 0; i < vecTexParam.size(); ++i)
	{
		Ptr<HHTexture> pCurTex = pMtrl->GetTextureParam(vecTexParam[i].ParamType);

		if (ParamUI::InputTexture(pCurTex, vecTexParam[i].strDesc, this, (DELEGATE_1)&MaterialUI::ChangeTexture))
		{
			pMtrl->SetTextureParam(vecTexParam[i].ParamType, pCurTex);
			m_SelectTexParam = vecTexParam[i].ParamType;
			SaveMaterialToFile();
		}
	}
}
