#include "pch.h"
#include "HHTilemapScript.h"

#include <Engine/HHTilemap.h>

HHTilemapScript::HHTilemapScript()
	: HHScript(UINT(SCRIPT_TYPE::TILEMAPSCRIPT))
{
	AddScriptParam(SCRIPT_PARAM::TEXTURE, "Test", &m_Texture);
}

HHTilemapScript::~HHTilemapScript()
{
}

void HHTilemapScript::Begin()
{
	/*Ptr<HHTexture> pTexture = HHAssetMgr::GetInstance()->Load<HHTexture>(L"Texture2D\\Sanctuary\\floor_tileset.png"
																		, L"Texture2D\\Sanctuary\\floor_tileset.png");

	Tilemap()->SetAtlasTexture(pTexture);
	Tilemap()->SetAtlasTileSize(Vec2(32.f, 32.f));*/
}

void HHTilemapScript::Tick()
{
}

void HHTilemapScript::SaveToFile(FILE* _File)
{
	SaveAssetReference(m_Texture, _File);
}

void HHTilemapScript::LoadFromFile(FILE* _File)
{
	LoadAssetReference(m_Texture, _File);
}
