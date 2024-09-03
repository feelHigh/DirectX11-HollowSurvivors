#include "pch.h"
#include "HHTextRenderer.h"

#include "HHGameObject.h"
#include "HHAssetMgr.h"

#include "HHText.h"
#include "HHFontMgr.h"

HHTextRenderer::HHTextRenderer()
	: HHRenderComponent(COMPONENT_TYPE::TEXTRENDERER)
{
	SetMesh(HHAssetMgr::GetInstance()->FindAsset<HHMesh>(L"RectMesh"));
	SetMaterial(HHAssetMgr::GetInstance()->FindAsset<HHMaterial>(L"BackgroundMtrl"));
}

HHTextRenderer::~HHTextRenderer()
{
}

void HHTextRenderer::FinalTick()
{
}

void HHTextRenderer::Render()
{
	HHText* pText = GetOwner()->GetUnComponent<HHText>(COMPONENT_TYPE::GAME_TEXT);
	if (nullptr != pText)
		pText->Render();
}

void HHTextRenderer::SaveToFile(FILE* _File)
{
	SaveDataToFile(_File);
}

void HHTextRenderer::LoadFromFile(FILE* _File)
{
	LoadDataFromFile(_File);
}
