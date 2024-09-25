#include "pch.h"
#include "HHTutorialMapScript.h"

HHTutorialMapScript::HHTutorialMapScript()
	: HHScript(UINT(SCRIPT_TYPE::TUTORIALMAPSCRIPT))
{
}

HHTutorialMapScript::~HHTutorialMapScript()
{
}

void HHTutorialMapScript::Begin()
{
	Ptr<HHTexture> BGTexture = HHAssetMgr::GetInstance()->Load<HHTexture>(L"Texture2D\\Tutorial\\Map.png"
																		, L"Texture2D\\Tutorial\\Map.png");
	GetRenderComponent()->GetDynamicMaterial()->SetTextureParam(TEX_0, BGTexture);
	//GetRenderComponent()->GetDynamicMaterial()->SetScalarParam(INT_0, 0);
}

void HHTutorialMapScript::Tick()
{
}

void HHTutorialMapScript::SaveToFile(FILE* _File)
{
	SaveAssetReference(m_Texture, _File);
}

void HHTutorialMapScript::LoadFromFile(FILE* _File)
{
	LoadAssetReference(m_Texture, _File);
}
