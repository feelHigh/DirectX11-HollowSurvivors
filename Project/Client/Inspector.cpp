#include "pch.h"
#include "Inspector.h"

#include <Engine/HHLevelMgr.h>
#include <Engine/HHLevel.h>
#include <Engine/HHLayer.h>
#include <Engine/HHGameObject.h>
#include <Engine/components.h>

#include "ComponentUI.h"
#include "AssetUI.h"
#include "ScriptUI.h"

Inspector::Inspector()
	: m_TargetObject(nullptr)
	, m_arrComponentUI{}
	, m_arrAssetUI{}
{
}

Inspector::~Inspector()
{
}

void Inspector::SetTargetObject(HHGameObject* _Object)
{
	m_TargetObject = _Object;

	// Object �� �����ϰ� �ִ� ������Ʈ�� �����ϴ� ������ƮUI �� Ȱ��ȭ ��
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr == m_arrComponentUI[i])
			continue;

		m_arrComponentUI[i]->SetTargetObject(_Object);
	}

	// Object �� �����ϰ� �ִ� Script ���� ScriptUI �� ������
	if (nullptr == m_TargetObject)
	{
		for (size_t i = 0; i < m_vecScriptUI.size(); ++i)
		{
			m_vecScriptUI[i]->SetTargetScript(nullptr);
		}
	}
	else
	{
		const vector<HHScript*>& vecScripts = m_TargetObject->GetScripts();

		// ��ũ��ƮUI ������ �����ϸ� �߰� ����
		if (m_vecScriptUI.size() < vecScripts.size())
		{
			CreateScriptUI((UINT)(vecScripts.size() - m_vecScriptUI.size()));
		}

		for (size_t i = 0; i < m_vecScriptUI.size(); ++i)
		{
			if (i < vecScripts.size())
				m_vecScriptUI[i]->SetTargetScript(vecScripts[i]);
			else
				m_vecScriptUI[i]->SetTargetScript(nullptr);
		}
	}

	// ���� UI ��Ȱ��ȭ
	m_TargetAsset = nullptr;
	for (UINT i = 0; i < (UINT)ASSET_TYPE::END; ++i)
	{
		m_arrAssetUI[i]->SetAsset(nullptr);
	}
}

void Inspector::SetTargetAsset(Ptr<HHAsset> _Asset)
{
	if (nullptr == _Asset)
		return;

	SetTargetObject(nullptr);

	m_TargetAsset = _Asset;

	for (UINT i = 0; i < (UINT)ASSET_TYPE::END; ++i)
	{
		m_arrAssetUI[i]->SetAsset(m_TargetAsset);
	}
}

void Inspector::Update()
{
	if (nullptr == m_TargetObject)
		return;

	SetTargetObject(m_TargetObject);

	// ===========
	// Object Name
	// ===========
	string strObjectName = string(m_TargetObject->GetName().begin(), m_TargetObject->GetName().end());
	ImGui::Text("Object Name");
	ImGui::SameLine(108);
	ImGui::InputText("##ObjectName", (char*)strObjectName.c_str(), strObjectName.length(), ImGuiInputTextFlags_ReadOnly);

	// ======
	// Layer
	// ======
	int LayerIdx = m_TargetObject->GetLayerIndex();
	HHLevel* pCurLevel = HHLevelMgr::GetInstance()->GetCurrentLevel();
	HHLayer* pLayer = pCurLevel->GetLayer(LayerIdx);
	string LayerName = string(pLayer->GetName().begin(), pLayer->GetName().end());

	char buffer[50] = {};

	if (LayerName.empty())
		sprintf_s(buffer, 50, "%d : %s", LayerIdx, "None");
	else
		sprintf_s(buffer, 50, "%d : %s", LayerIdx, LayerName.c_str());

	ImGui::Text("Layer");
	ImGui::SameLine(108);
	ImGui::InputText("##LayerName", buffer, strlen(buffer), ImGuiInputTextFlags_ReadOnly);
}
