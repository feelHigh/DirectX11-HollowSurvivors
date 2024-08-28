#include "pch.h"
#include "HHMenuButtonScript.h"

HHMenuButtonScript::HHMenuButtonScript()
	: HHScript(UINT(SCRIPT_TYPE::MENUBUTTONSCRIPT))
	, m_Speed(400.f)
{
}

HHMenuButtonScript::~HHMenuButtonScript()
{
}

void HHMenuButtonScript::Begin()
{
}

void HHMenuButtonScript::Tick()
{
}

void HHMenuButtonScript::BeginOverlap(HHCollider2D* _OwnCollider, HHGameObject* _OtherObject, HHCollider2D* _OtherCollider)
{
	if (_OtherCollider->GetOwner()->GetName() == L"Level Foreground2")
	{
		DeleteObject(_OtherObject);
		//return;
	}
}

void HHMenuButtonScript::SaveToFile(FILE* _File)
{
	fwrite(&m_Speed, sizeof(float), 1, _File);
	SaveAssetReference(m_Texture, _File);
}

void HHMenuButtonScript::LoadFromFile(FILE* _File)
{
	fread(&m_Speed, sizeof(float), 1, _File);
	LoadAssetReference(m_Texture, _File);
}
