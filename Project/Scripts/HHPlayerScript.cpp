#include "pch.h"
#include "HHPlayerScript.h"

#include "HHMissileScript.h"

HHPlayerScript::HHPlayerScript()
	: HHScript(UINT(SCRIPT_TYPE::PLAYERSCRIPT))
	, m_Speed(400.f)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, "PlayerSpeed", &m_Speed);
	AddScriptParam(SCRIPT_PARAM::TEXTURE, "Test", &m_Texture);
	AddScriptParam(SCRIPT_PARAM::PREFAB, "Missile", &m_MissilePref);
}

HHPlayerScript::~HHPlayerScript()
{
}

void HHPlayerScript::Begin()
{
	GetRenderComponent()->GetDynamicMaterial();

	//m_MissilePref = HHAssetMgr::GetInstance()->FindAsset<HHPrefab>(L"MissilePref");
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


	if (KEY_PRESSED(KEY::Z))
	{
		//MeshRender()->GetMaterial()->SetScalarParam(INT_0, 1);
		Vec3 vRot = Transform()->GetRelativeRoatation();
		vRot.z += DT * XM_PI;
		Transform()->SetRelativeRotation(vRot);

		/*	Vec3 vScale = Transform()->GetRelativeScale();
			vScale += DT * 100.f * Vec3(1.f, 1.f, 1.f);
			Transform()->SetRelativeScale(vScale);*/
	}
	else
	{
		//MeshRender()->GetMaterial()->SetScalarParam(INT_0, 0);
	}

	if (KEY_TAP(KEY::SPACE))
	{
		// 미사일 발사
		if (nullptr != m_MissilePref)
		{
			Instantiate(m_MissilePref, 5, Transform()->GetWorldPosition(), L"Missile");
		}
	}

	Transform()->SetRelativePosition(vPos);
}

void HHPlayerScript::BeginOverlap(HHCollider2D* _OwnCollider, HHGameObject* _OtherObject, HHCollider2D* _OtherCollider)
{
	DeleteObject(_OtherObject);

	Vec3 vScale = Transform()->GetRelativeScale();

	vScale += Vec3(10.f, 10.f, 0.f);
	Collider2D()->SetScale(Collider2D()->GetScale() + Vec3(10.f, 10.f, 0.f));

	Transform()->SetRelativeScale(vScale);
}

void HHPlayerScript::SaveToFile(FILE* _File)
{
	fwrite(&m_Speed, sizeof(float), 1, _File);
	SaveAssetReference(m_Texture, _File);
	SaveAssetReference(m_MissilePref, _File);
}

void HHPlayerScript::LoadFromFile(FILE* _File)
{
	fread(&m_Speed, sizeof(float), 1, _File);
	LoadAssetReference(m_Texture, _File);
	LoadAssetReference(m_MissilePref, _File);
}
