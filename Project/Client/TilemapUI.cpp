#include "pch.h"
#include "TilemapUI.h"

TilemapUI::TilemapUI()
	: ComponentUI(COMPONENT_TYPE::TILEMAP)
{
}

TilemapUI::~TilemapUI()
{
}

void TilemapUI::Update()
{
	Title();
}
