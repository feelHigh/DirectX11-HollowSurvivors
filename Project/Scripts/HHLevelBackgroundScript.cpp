#include "pch.h"
#include "HHLevelBackgroundScript.h"

HHLevelBackgroundScript::HHLevelBackgroundScript()
	: HHScript(UINT(SCRIPT_TYPE::LEVELBACKGROUNDSCRIPT))
{
	AddScriptParam(SCRIPT_PARAM::TEXTURE, "Test", &m_Texture);
}

HHLevelBackgroundScript::~HHLevelBackgroundScript()
{
}

void HHLevelBackgroundScript::Begin()
{
	Ptr<HHTexture> BGTexture = HHAssetMgr::GetInstance()->Load<HHTexture>(L"Texture2D\\Title\\HollowSurvivorsArtwork3-alpha.png"
																		, L"Texture2D\\Title\\HollowSurvivorsArtwork3-alpha.png");
	GetRenderComponent()->GetDynamicMaterial()->SetTextureParam(TEX_0, BGTexture);
	//GetRenderComponent()->GetDynamicMaterial()->SetScalarParam(INT_0, 0);
}

void HHLevelBackgroundScript::Tick()
{
}

void HHLevelBackgroundScript::SaveToFile(FILE* _File)
{
	SaveAssetReference(m_Texture, _File);
}

void HHLevelBackgroundScript::LoadFromFile(FILE* _File)
{
	LoadAssetReference(m_Texture, _File);
}
