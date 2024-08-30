#include "pch.h"
#include "HHMouseCursorScript.h"

#include <Engine/HHDevice.h>
#include <Engine/HHKeyMgr.h>

HHMouseCursorScript::HHMouseCursorScript()
	: HHScript(UINT(SCRIPT_TYPE::MOUSECURSORSCRIPT))
{
	AddScriptParam(SCRIPT_PARAM::TEXTURE, "Test", &m_Texture);
}

HHMouseCursorScript::~HHMouseCursorScript()
{
}

void HHMouseCursorScript::Begin()
{
	Ptr<HHTexture> MouseCursorTexture = HHAssetMgr::GetInstance()->Load<HHTexture>(L"Texture2D\\UI\\crosshair-PIXELLarger-alpha.png"
																				 , L"Texture2D\\UI\\crosshair-PIXELLarger-alpha.png");
	GetRenderComponent()->GetDynamicMaterial()->SetTextureParam(TEX_0, MouseCursorTexture);
	//GetRenderComponent()->GetDynamicMaterial()->SetScalarParam(INT_0, 0);
}

void HHMouseCursorScript::Tick()
{
	Vec2 vPos = HHKeyMgr::GetInstance()->GetMousePos();

	vPos.x *= -1.f;
	vPos.y *= -1.f;

	vPos.x += HHDevice::GetInstance()->GetResolution().x / 2.f;
	vPos.y += HHDevice::GetInstance()->GetResolution().y / 2.f;

	Transform()->SetRelativePosition(Vec3(vPos.x, vPos.y, 1.f));
}

void HHMouseCursorScript::BeginOverlap(HHCollider2D* _OwnCollider, HHGameObject* _OtherObject, HHCollider2D* _OtherCollider)
{
}

void HHMouseCursorScript::SaveToFile(FILE* _File)
{
	SaveAssetReference(m_Texture, _File);
}

void HHMouseCursorScript::LoadFromFile(FILE* _File)
{
	LoadAssetReference(m_Texture, _File);
}
