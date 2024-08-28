#include "pch.h"
#include "HHSmallGirlScript.h"

HHSmallGirlScript::HHSmallGirlScript()
	: HHScript(UINT(SCRIPT_TYPE::SMALLGIRLSCRIPT))
	, m_Speed(400.f)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, "NPCSpeed", &m_Speed);
	AddScriptParam(SCRIPT_PARAM::TEXTURE, "Test", &m_Texture);
}

HHSmallGirlScript::~HHSmallGirlScript()
{
}

void HHSmallGirlScript::Begin()
{
	Ptr<HHTexture> FGTexture = HHAssetMgr::GetInstance()->Load<HHTexture>(L"Texture2D\\Sanctuary\\Npc\\SmallGirl.png"
																		, L"Texture2D\\Sanctuary\\Npc\\SmallGirl.png");
	GetRenderComponent()->GetDynamicMaterial()->SetTextureParam(TEX_0, FGTexture);
	//GetRenderComponent()->GetDynamicMaterial()->SetScalarParam(INT_0, 0);
}

void HHSmallGirlScript::Tick()
{
	Vec3 vPos = Transform()->GetRelativePosition();

	if (KEY_PRESSED(KEY::LEFT))
		vPos.x -= DT * m_Speed;
	if (KEY_PRESSED(KEY::RIGHT))
		vPos.x += DT * m_Speed;
	if (KEY_PRESSED(KEY::UP))
		vPos.y += DT * m_Speed;
	if (KEY_PRESSED(KEY::DOWN))
		vPos.y -= DT * m_Speed;


	//Transform()->SetRelativePosition(vPos);
}

void HHSmallGirlScript::BeginOverlap(HHCollider2D* _OwnCollider, HHGameObject* _OtherObject, HHCollider2D* _OtherCollider)
{
	//DeleteObject(_OtherObject);

}

void HHSmallGirlScript::SaveToFile(FILE* _File)
{
	fwrite(&m_Speed, sizeof(float), 1, _File);
	SaveAssetReference(m_Texture, _File);
}

void HHSmallGirlScript::LoadFromFile(FILE* _File)
{
	fread(&m_Speed, sizeof(float), 1, _File);
	LoadAssetReference(m_Texture, _File);
}
