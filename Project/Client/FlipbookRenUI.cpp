#include "pch.h"
#include "FlipbookRenUI.h"

FlipbookRenUI::FlipbookRenUI()
	: ComponentUI(COMPONENT_TYPE::FLIPBOOK_RENDERER)
{
}

FlipbookRenUI::~FlipbookRenUI()
{
}

void FlipbookRenUI::Update()
{
	Title();
}
