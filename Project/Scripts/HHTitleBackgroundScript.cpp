#include "pch.h"
#include "HHTitleBackgroundScript.h"

HHTitleBackgroundScript::HHTitleBackgroundScript()
	: HHScript(UINT(SCRIPT_TYPE::TITLEBACKGROUNDSCRIPT))
{
	AddScriptParam(SCRIPT_PARAM::TEXTURE, "Test", &m_Texture);
}

HHTitleBackgroundScript::~HHTitleBackgroundScript()
{
}

void HHTitleBackgroundScript::Begin()
{
	Ptr<HHTexture> BGTexture = HHAssetMgr::GetInstance()->Load<HHTexture>(L"Texture2D\\Title\\HollowSurvivorsArtwork3-alpha.png"
																		, L"Texture2D\\Title\\HollowSurvivorsArtwork3-alpha.png");
	GetRenderComponent()->GetDynamicMaterial()->SetTextureParam(TEX_0, BGTexture);
	//GetRenderComponent()->GetDynamicMaterial()->SetScalarParam(INT_0, 0);
}

void HHTitleBackgroundScript::Tick()
{
}

void HHTitleBackgroundScript::SaveToFile(FILE* _File)
{
	SaveAssetReference(m_Texture, _File);
}

void HHTitleBackgroundScript::LoadFromFile(FILE* _File)
{
	LoadAssetReference(m_Texture, _File);
}
