#include "pch.h"
#include "HHLight2D.h"

#include "HHTransform.h"
#include "HHRenderMgr.h"

HHLight2D::HHLight2D()
	: HHComponent(COMPONENT_TYPE::LIGHT2D)
	, m_Info{}
{
}

HHLight2D::~HHLight2D()
{
}

void HHLight2D::FinalTick()
{
	m_Info.WorldPosition = Transform()->GetWorldPosition();
	m_Info.WorldDirection = Transform()->GetWorldDirection(DIRECTION_TYPE::RIGHT);

	// 자신을 RenderMgr 에 등록시킴 (광원 등록)
	HHRenderMgr::GetInstance()->RegisterLight2D(this);
}

void HHLight2D::SetLightType(LIGHT_TYPE _Type)
{
	m_Info.Type = _Type;
}

void HHLight2D::SaveToFile(FILE* _File)
{
	fwrite(&m_Info, sizeof(tLightInfo), 1, _File);
}

void HHLight2D::LoadFromFile(FILE* _File)
{
	fread(&m_Info, sizeof(tLightInfo), 1, _File);
}
