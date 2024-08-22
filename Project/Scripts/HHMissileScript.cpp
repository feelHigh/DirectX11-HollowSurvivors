#include "pch.h"
#include "HHMissileScript.h"

HHMissileScript::HHMissileScript()
	: HHScript(UINT(SCRIPT_TYPE::MISSILESCRIPT))
	, m_Speed(1000.f)
{
}

HHMissileScript::~HHMissileScript()
{
}

void HHMissileScript::Begin()
{
	GetRenderComponent()->GetDynamicMaterial();

	Ptr<HHMaterial> pMtrl = GetRenderComponent()->GetMaterial();

	if (nullptr != pMtrl)
	{
		Ptr<HHTexture> pTexture = HHAssetMgr::GetInstance()->Load<HHTexture>(L"texture\\Idle_Left.bmp", L"texture\\Idle_Left.bmp");
		pMtrl->SetTextureParam(TEX_0, pTexture);
	}
}

void HHMissileScript::Tick()
{
	Vec3 vPos = Transform()->GetRelativePosition();

	vPos.y += DT * m_Speed;

	Transform()->SetRelativePosition(vPos);
}

void HHMissileScript::BeginOverlap(HHCollider2D* _OwnCollider, HHGameObject* _OtherObject, HHCollider2D* _OtherCollider)
{
	DeleteObject(_OtherObject);
}

void HHMissileScript::SaveToFile(FILE* _File)
{
	fwrite(&m_Speed, 4, 1, _File);
}

void HHMissileScript::LoadFromFile(FILE* _File)
{
	fread(&m_Speed, 4, 1, _File);
}
