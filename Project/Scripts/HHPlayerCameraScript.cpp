#include "pch.h"
#include "HHPlayerCameraScript.h"

HHPlayerCameraScript::HHPlayerCameraScript()
	: HHScript(UINT(SCRIPT_TYPE::CAMERAMOVESCRIPT))
	, m_CamSpeed(500.f)
{
}

HHPlayerCameraScript::~HHPlayerCameraScript()
{
}

void HHPlayerCameraScript::Tick()
{
	if (PROJECTION_TYPE::PERSPECTIVE == Camera()->GetProjectionType())
	{
		PerspectiveMovement();
	}
}

void HHPlayerCameraScript::PerspectiveMovement()
{
	float Speed = m_CamSpeed;

	if (KEY_PRESSED(KEY::LSHIFT))
	{
		Speed *= 3.f;
	}

	Vec3 vFront = Transform()->GetRelativeDirection(DIRECTION_TYPE::FRONT);
	Vec3 vRight = Transform()->GetRelativeDirection(DIRECTION_TYPE::RIGHT);

	Vec3 vPos = Transform()->GetRelativePosition();


	Transform()->SetRelativePosition(vPos);
}

void HHPlayerCameraScript::SaveToFile(FILE* _File)
{
	//fwrite(&m_CamSpeed, sizeof(float), 1, _File);
}

void HHPlayerCameraScript::LoadFromFile(FILE* _File)
{
	//fread(&m_CamSpeed, sizeof(float), 1, _File);
}
