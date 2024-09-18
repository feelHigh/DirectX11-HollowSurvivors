#include "pch.h"
#include "HHTitleLogoScript.h"

HHTitleLogoScript::HHTitleLogoScript()
	: HHScript(UINT(SCRIPT_TYPE::TITLELOGOSCRIPT))
{
	AddScriptParam(SCRIPT_PARAM::TEXTURE, "Test", &m_Texture);
}

HHTitleLogoScript::~HHTitleLogoScript()
{
}

void HHTitleLogoScript::Begin()
{
	Ptr<HHTexture> pTexture = HHAssetMgr::GetInstance()->Load<HHTexture>(L"Texture2D\\Title\\Hollow18-alpha.png"
																		, L"Texture2D\\Title\\Hollow18-alpha.png");

	GetRenderComponent()->GetDynamicMaterial()->SetTextureParam(TEX_0, pTexture);
}

void HHTitleLogoScript::Tick()
{
}

void HHTitleLogoScript::BeginOverlap(HHCollider2D* _OwnCollider, HHGameObject* _OtherObject, HHCollider2D* _OtherCollider)
{
}

void HHTitleLogoScript::SaveToFile(FILE* _File)
{
	SaveAssetReference(m_Texture, _File);
}

void HHTitleLogoScript::LoadFromFile(FILE* _File)
{
	LoadAssetReference(m_Texture, _File);
}
