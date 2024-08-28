#include "pch.h"
#include "HHPlayerScript.h"

HHPlayerScript::HHPlayerScript()
	: HHScript(UINT(SCRIPT_TYPE::PLAYERSCRIPT))
	, m_Speed(400.f)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, "PlayerSpeed", &m_Speed);
	AddScriptParam(SCRIPT_PARAM::TEXTURE, "Test", &m_Texture);
}

HHPlayerScript::~HHPlayerScript()
{
}

void HHPlayerScript::Begin()
{
	Ptr<HHTexture> FGTexture = HHAssetMgr::GetInstance()->Load<HHTexture>(L"Texture2D\\Title\\Hollow18-alpha.png"
																		, L"Texture2D\\Title\\Hollow18-alpha.png");
	GetRenderComponent()->GetDynamicMaterial()->SetTextureParam(TEX_0, FGTexture);
	//GetRenderComponent()->GetDynamicMaterial()->SetScalarParam(INT_0, 0);
}

void HHPlayerScript::Tick()
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


	Transform()->SetRelativePosition(vPos);
}

void HHPlayerScript::BeginOverlap(HHCollider2D* _OwnCollider, HHGameObject* _OtherObject, HHCollider2D* _OtherCollider)
{
	if (_OtherCollider->GetOwner()->GetName() == L"Level Foreground2")
	{
		DeleteObject(_OtherObject);
		//return;
	}
}

void HHPlayerScript::SaveToFile(FILE* _File)
{
	fwrite(&m_Speed, sizeof(float), 1, _File);
	SaveAssetReference(m_Texture, _File);
}

void HHPlayerScript::LoadFromFile(FILE* _File)
{
	fread(&m_Speed, sizeof(float), 1, _File);
	LoadAssetReference(m_Texture, _File);
}
