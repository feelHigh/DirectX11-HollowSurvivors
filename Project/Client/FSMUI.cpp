#include "pch.h"
#include "FSMUI.h"

FSMUI::FSMUI()
	: AssetUI(ASSET_TYPE::FSM)
{
}

FSMUI::~FSMUI()
{
}

void FSMUI::Update()
{
	Title();
}