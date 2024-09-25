#include "pch.h"
#include "HHTutorialBackgroundCloudScript.h"

HHTutorialBackgroundCloudScript::HHTutorialBackgroundCloudScript()
	: HHScript(UINT(SCRIPT_TYPE::TUTORIALBACKGROUNDCLOUDSCRIPT))
{
}

HHTutorialBackgroundCloudScript::~HHTutorialBackgroundCloudScript()
{
}

void HHTutorialBackgroundCloudScript::Begin()
{
	Ptr<HHTexture> BGTexture = HHAssetMgr::GetInstance()->Load<HHTexture>(L"Texture2D\\Tutorial\\TutorialForeground-1.png"
																		, L"Texture2D\\Tutorial\\TutorialForeground-1.png");
	GetRenderComponent()->GetDynamicMaterial()->SetTextureParam(TEX_0, BGTexture);
	//GetRenderComponent()->GetDynamicMaterial()->SetScalarParam(INT_0, 0);
}

void HHTutorialBackgroundCloudScript::Tick()
{
}

void HHTutorialBackgroundCloudScript::SaveToFile(FILE* _File)
{
	SaveAssetReference(m_Texture, _File);
}

void HHTutorialBackgroundCloudScript::LoadFromFile(FILE* _File)
{
	LoadAssetReference(m_Texture, _File);
}
