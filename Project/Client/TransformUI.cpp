#include "pch.h"
#include "TransformUI.h"

#include <Engine/HHGameObject.h>
#include <Engine/HHTransform.h>

TransformUI::TransformUI()
	: ComponentUI(COMPONENT_TYPE::TRANSFORM)
{
}

TransformUI::~TransformUI()
{
}

void TransformUI::Update()
{
	Title();

	HHTransform* pTrans = GetTargetObject()->Transform();

	Vec3 vPos = pTrans->GetRelativePosition();
	Vec3 vScale = pTrans->GetRelativeScale();
	Vec3 vRot = pTrans->GetRelativeRoatation();
	vRot = (vRot / XM_PI) * 180.f;

	ImGui::Text("Position");
	ImGui::SameLine(100);
	ImGui::DragFloat3("##Pos", vPos);

	ImGui::Text("Scale");
	ImGui::SameLine(100);
	ImGui::DragFloat3("##Scale", vScale);

	ImGui::Text("Rotation");
	ImGui::SameLine(100);
	ImGui::DragFloat3("##Rot", vRot, 0.1f);

	pTrans->SetRelativePosition(vPos);
	pTrans->SetRelativeScale(vScale);

	vRot = (vRot / 180.f) * XM_PI;
	pTrans->SetRelativeRotation(vRot);

	// Independent Scale
	
	bool Is = pTrans->IsIndependentScale();

	ImGui::Text("Ignore Parent");
	ImGui::SameLine(100);
	if (ImGui::Checkbox("##TransIS", &Is))
	{
		pTrans->SetIndependentScale(Is);
	}
	
}