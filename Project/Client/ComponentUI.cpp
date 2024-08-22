#include "pch.h"
#include "ComponentUI.h"

#include <Engine/HHGameObject.h>
#include <Engine/HHComponent.h>

ComponentUI::ComponentUI(COMPONENT_TYPE _Type)
	: m_TargetObject(nullptr)
	, m_Type(_Type)
{
	SetChildBorder(true);
}

ComponentUI::~ComponentUI()
{
}

void ComponentUI::SetTargetObject(HHGameObject* _Object)
{
	m_TargetObject = _Object;

	// 타겟 오브젝트가 없거나, 타겟 오브젝트가 컴포넌트UI 담당 컴포넌트를 보유하고 있지 않다며
	// 컴포넌트UI 를 비활성화 한다.
	if (nullptr != m_TargetObject &&
		nullptr != m_TargetObject->GetComponent(m_Type))
	{
		SetActive(true);
	}

	else
	{
		SetActive(false);
	}
}

void ComponentUI::Title()
{
	ImGui::PushID((int)m_Type);
	//ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.f, 0.7f, 0.8f));
	//ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.f, 0.7f, 0.8f));
	//ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.f, 0.7f, 0.8f));

	ImGui::Button(ToString(m_Type));

	//ImGui::PopStyleColor(3);
	ImGui::PopID();
}
