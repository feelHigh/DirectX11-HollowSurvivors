#include "pch.h"
#include "HHButtonScript.h"

#include <Engine/HHLevelMgr.h>
#include <Client/HHLoadGameLevel.h>

HHButtonScript::HHButtonScript()
	: HHScript(UINT(SCRIPT_TYPE::BUTTONSCRIPT))
{
}

HHButtonScript::~HHButtonScript()
{
}

void HHButtonScript::Begin()
{
}

void HHButtonScript::Tick()
{
}

void HHButtonScript::BeginOverlap(HHCollider2D* _OwnCollider, HHGameObject* _OtherObject, HHCollider2D* _OtherCollider)
{
}

void HHButtonScript::Overlap(HHCollider2D* _OwnCollider, HHGameObject* _OtherObject, HHCollider2D* _OtherCollider)
{
	m_ButtonType = GetOwner()->Button()->GetButtonType();

	if (m_ButtonType == BUTTON_TYPE::TITLE_PLAY && _OtherCollider->GetOwner()->GetName() == L"Mouse Cursor")
	{
		if (KEY_PRESSED(KEY::LBTN))
		{
			HHLoadGameLevel::GetInstance()->ChangeLevelByName(L"SanctuaryLevel", LEVEL_STATE::PLAY);
		}
	}
}

void HHButtonScript::EndOverlap(HHCollider2D* _OwnCollider, HHGameObject* _OtherObject, HHCollider2D* _OtherCollider)
{
}

void HHButtonScript::SaveToFile(FILE* _File)
{
	SaveAssetReference(m_Texture, _File);
}

void HHButtonScript::LoadFromFile(FILE* _File)
{
	LoadAssetReference(m_Texture, _File);
}
