#include "pch.h"
#include "HHTutorialBackgroundScript.h"

HHTutorialBackgroundScript::HHTutorialBackgroundScript()
	: HHScript(UINT(SCRIPT_TYPE::TUTORIALBACKGROUNDSCRIPT))
{
}

HHTutorialBackgroundScript::~HHTutorialBackgroundScript()
{
}

void HHTutorialBackgroundScript::Begin()
{
	Ptr<HHTexture> BGTexture = HHAssetMgr::GetInstance()->Load<HHTexture>(L"Texture2D\\Tutorial\\TutorialBackground.png"
																		, L"Texture2D\\Tutorial\\TutorialBackground.png");
	GetRenderComponent()->GetDynamicMaterial()->SetTextureParam(TEX_0, BGTexture);
	//GetRenderComponent()->GetDynamicMaterial()->SetScalarParam(INT_0, 0);
}

void HHTutorialBackgroundScript::Tick()
{
}

void HHTutorialBackgroundScript::SaveToFile(FILE* _File)
{
	SaveAssetReference(m_Texture, _File);
}

void HHTutorialBackgroundScript::LoadFromFile(FILE* _File)
{
	LoadAssetReference(m_Texture, _File);
}
