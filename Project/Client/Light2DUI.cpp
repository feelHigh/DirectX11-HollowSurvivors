#include "pch.h"
#include "Light2DUI.h"

#include <Engine/HHGameObject.h>
#include <Engine/HHLight2D.h>

Light2DUI::Light2DUI()
	: ComponentUI(COMPONENT_TYPE::LIGHT2D)
{
}

Light2DUI::~Light2DUI()
{
}

void Light2DUI::Update()
{
	Title();

	LIGHT_TYPE eType = GetTargetObject()->Light2D()->GetLightType();

	SelectLightType(eType);
}

void Light2DUI::SelectLightType(LIGHT_TYPE SelectLight)
{
	if (SelectLight == LIGHT_TYPE::DIRECTIONAL)
	{
		LIGHT_TYPE eType = GetTargetObject()->Light2D()->GetLightType();
		ImGui::Text("Type   "); ImGui::SameLine(); ImGui::Combo("##LightType", (int*)&eType, "Directional\0Point\0Spot\0");
		GetTargetObject()->Light2D()->SetLightType(eType);

		Vec3 vAmbient = GetTargetObject()->Light2D()->GetLightAmbient();
		ImGui::Text("Ambient "); ImGui::SameLine(); ImGui::ColorEdit3("##LightAmbient", vAmbient);
		GetTargetObject()->Light2D()->SetLightAmbient(vAmbient);
	}
	else if (SelectLight == LIGHT_TYPE::POINT)
	{
		LIGHT_TYPE eType = GetTargetObject()->Light2D()->GetLightType();
		ImGui::Text("Type   "); ImGui::SameLine(); ImGui::Combo("##LightType", (int*)&eType, "Directional\0Point\0Spot\0");
		GetTargetObject()->Light2D()->SetLightType(eType);

		Vec3 vColor = GetTargetObject()->Light2D()->GetLightColor();
		ImGui::Text("Color   "); ImGui::SameLine(); ImGui::ColorEdit3("##LightColor", vColor);
		GetTargetObject()->Light2D()->SetLightColor(vColor);

		float fRadius = GetTargetObject()->Light2D()->GetRadius();
		ImGui::Text("Radius "); ImGui::SameLine(); ImGui::DragFloat("##LightRadius", &fRadius);
		GetTargetObject()->Light2D()->SetRadius(fRadius);
	}
	else if (SelectLight == LIGHT_TYPE::SPOT)
	{
		LIGHT_TYPE eType = GetTargetObject()->Light2D()->GetLightType();
		ImGui::Text("Type   "); ImGui::SameLine(); ImGui::Combo("##LightType", (int*)&eType, "Directional\0Point\0Spot\0");
		GetTargetObject()->Light2D()->SetLightType(eType);

		Vec3 vColor = GetTargetObject()->Light2D()->GetLightColor();
		ImGui::Text("Color   "); ImGui::SameLine(); ImGui::ColorEdit3("##LightColor", vColor);
		GetTargetObject()->Light2D()->SetLightColor(vColor);

		float fRadius = GetTargetObject()->Light2D()->GetRadius();
		ImGui::Text("Radius "); ImGui::SameLine(); ImGui::DragFloat("##LightRadius", &fRadius);
		GetTargetObject()->Light2D()->SetRadius(fRadius);

		float fAngle = GetTargetObject()->Light2D()->GetAngle();
		ImGui::Text("Angle  "); ImGui::SameLine(); ImGui::DragFloat("##LightAngle", &fAngle);
		GetTargetObject()->Light2D()->SetAngle(fAngle);
	}
}
