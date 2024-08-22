#include "pch.h"
#include "HHRenderComponent.h"

#include "HHAssetMgr.h"
#include "HHLevelMgr.h"
#include "HHLevel.h"

HHRenderComponent::HHRenderComponent(COMPONENT_TYPE _Type)
	: HHComponent(_Type)
	, m_Mesh(nullptr)
	, m_Material(nullptr)
{
}

HHRenderComponent::HHRenderComponent(const HHRenderComponent& _Origin)
	: HHComponent(_Origin)
	, m_Mesh(_Origin.m_Mesh)
	, m_Material(_Origin.m_Material)
	, m_SharedMaterial(_Origin.m_Material)
{
	HHLevel* pCurLevel = HHLevelMgr::GetInstance()->GetCurrentLevel();
	if (nullptr != pCurLevel)
	{
		assert(!(pCurLevel->GetState() != LEVEL_STATE::PLAY && nullptr != _Origin.m_DynamicMaterial));
	}

	if (nullptr != _Origin.m_DynamicMaterial)
	{
		GetDynamicMaterial();
	}
}

HHRenderComponent::~HHRenderComponent()
{
}

void HHRenderComponent::SetMaterial(Ptr<HHMaterial> _Material)
{
	m_Material = m_SharedMaterial = _Material;
}

Ptr<HHMaterial> HHRenderComponent::GetSharedMaterial()
{
	m_Material = m_SharedMaterial;
	return m_Material;
}

Ptr<HHMaterial> HHRenderComponent::GetDynamicMaterial()
{
	// 동적재질 생성 및 반환은 게임(레벨) 이 Play 모드인 경우에만 호출이 되어야 한다.
	assert(HHLevelMgr::GetInstance()->GetCurrentLevel()->GetState() == LEVEL_STATE::PLAY);

	if (nullptr != m_DynamicMaterial)
		return m_Material = m_DynamicMaterial;

	m_Material = m_DynamicMaterial = m_SharedMaterial->Clone();

	return m_Material;
}

void HHRenderComponent::SaveDataToFile(FILE* _File)
{
	SaveAssetReference(m_Mesh, _File);
	SaveAssetReference(m_Material, _File);
	SaveAssetReference(m_SharedMaterial, _File);
}

void HHRenderComponent::LoadDataFromFile(FILE* _File)
{
	LoadAssetReference(m_Mesh, _File);
	LoadAssetReference(m_Material, _File);
	LoadAssetReference(m_SharedMaterial, _File);
}
