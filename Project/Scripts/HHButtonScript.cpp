#include "pch.h"
#include "HHButtonScript.h"

#include <Engine/HHLevelMgr.h>

HHButtonScript::HHButtonScript()
	: HHScript(UINT(SCRIPT_TYPE::BUTTONSCRIPT))
{
}

HHButtonScript::~HHButtonScript()
{
}

void HHButtonScript::Begin()
{
	/*Ptr<HHTexture> MouseCursorTexture = HHAssetMgr::GetInstance()->Load<HHTexture>(L"Texture2D\\UI\\crosshair-PIXELLarger-alpha.png"
																				 , L"Texture2D\\UI\\crosshair-PIXELLarger-alpha.png");
	GetRenderComponent()->GetDynamicMaterial()->SetTextureParam(TEX_0, MouseCursorTexture);*/
	//GetRenderComponent()->GetDynamicMaterial()->SetScalarParam(INT_0, 0);
}

void HHButtonScript::Tick()
{
}

void HHButtonScript::BeginOverlap(HHCollider2D* _OwnCollider, HHGameObject* _OtherObject, HHCollider2D* _OtherCollider)
{
	if (BUTTON_TYPE::TITLE_PLAY && _OtherCollider->GetOwner()->GetName() == L"Mouse Cursor")
	{
		//ChangeLevel()
	}
}

void HHButtonScript::Overlap(HHCollider2D* _OwnCollider, HHGameObject* _OtherObject, HHCollider2D* _OtherCollider)
{
}

void HHButtonScript::EndOverlap(HHCollider2D* _OwnCollider, HHGameObject* _OtherObject, HHCollider2D* _OtherCollider)
{
}

void HHButtonScript::SaveToFile(FILE* _File)
{
	SaveAssetReference(m_Texture, _File);
}

void HHButtonScript::LoadFromFile(FILE* _File)
{
	LoadAssetReference(m_Texture, _File);
}
