#include "pch.h"
#include "HHButton.h"

#include "HHKeyMgr.h"
#include "HHCollider2D.h"
#include "HHGameObject.h"

HHButton::HHButton()
	: HHComponent(COMPONENT_TYPE::GAME_BUTTON)
{
}

HHButton::~HHButton()
{
}

void HHButton::Begin()
{
}

void HHButton::Tick()
{
}

void HHButton::FinalTick()
{
}

void HHButton::SaveToFile(FILE* _File)
{
	fwrite(&mType, sizeof(BUTTON_TYPE), 1, _File);
}

void HHButton::LoadFromFile(FILE* _File)
{
	fread(&mType, sizeof(BUTTON_TYPE), 1, _File);
}
