#include "pch.h"
#include "HHCameraMoveScript.h"

HHCameraMoveScript::HHCameraMoveScript()
	: HHScript(UINT(SCRIPT_TYPE::CAMERAMOVESCRIPT))
	, m_CamSpeed(500.f)
{
}

HHCameraMoveScript::~HHCameraMoveScript()
{
}

void HHCameraMoveScript::Tick()
{
	if (PROJECTION_TYPE::ORTHOGRAPHIC == Camera()->GetProjectionType())
	{
		OrthographicMovement();
	}
	else if (PROJECTION_TYPE::PERSPECTIVE == Camera()->GetProjectionType())
	{
		PerspectiveMovement();
	}

	if (KEY_TAP(KEY::P))
	{
		if (PROJECTION_TYPE::ORTHOGRAPHIC == Camera()->GetProjectionType())
			Camera()->SetProjectionType(PROJECTION_TYPE::PERSPECTIVE);
		else
			Camera()->SetProjectionType(PROJECTION_TYPE::ORTHOGRAPHIC);
	}
}

void HHCameraMoveScript::OrthographicMovement()
{
	float Speed = m_CamSpeed;

	if (KEY_PRESSED(KEY::LSHIFT))
	{
		Speed *= 3.f;
	}

	Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
	Vec3 vPos = Transform()->GetRelativePosition();

	if (KEY_PRESSED(KEY::W))
	{
		vPos.y += DT * Speed;
	}

	if (KEY_PRESSED(KEY::S))
	{
		vPos.y -= DT * Speed;
	}

	if (KEY_PRESSED(KEY::A))
	{
		vPos.x -= DT * Speed;
	}

	if (KEY_PRESSED(KEY::D))
	{
		vPos.x += DT * Speed;
	}

	Transform()->SetRelativePosition(vPos);
}

void HHCameraMoveScript::PerspectiveMovement()
{
	float Speed = m_CamSpeed;

	if (KEY_PRESSED(KEY::LSHIFT))
	{
		Speed *= 3.f;
	}

	Vec3 vFront = Transform()->GetRelativeDirection(DIRECTION_TYPE::FRONT);
	Vec3 vRight = Transform()->GetRelativeDirection(DIRECTION_TYPE::RIGHT);

	Vec3 vPos = Transform()->GetRelativePosition();

	if (KEY_PRESSED(KEY::W))
	{
		vPos += vFront * DT * Speed;
	}

	if (KEY_PRESSED(KEY::S))
	{
		vPos -= vFront * DT * Speed;
	}

	if (KEY_PRESSED(KEY::A))
	{
		vPos -= vRight * DT * Speed;
	}

	if (KEY_PRESSED(KEY::D))
	{
		vPos += vRight * DT * Speed;
	}

	Transform()->SetRelativePosition(vPos);

	if (KEY_PRESSED(KEY::RBTN))
	{
		HHKeyMgr::GetInstance()->MouseCapture(true);

		// ���콺�� �̵��ϴ� ����
		//vDir.x; ==> y�� ȸ��;
		//vDir.y; ==> x�� ȸ��
		Vec2 vDir = HHKeyMgr::GetInstance()->GetDragDir();

		Vec3 vRot = Transform()->GetRelativeRoatation();
		vRot.y += vDir.x * XM_PI * DT * 10.f;
		vRot.x += vDir.y * XM_PI * DT * 10.f;
		Transform()->SetRelativeRotation(vRot);
	}
	else if (KEY_RELEASED(KEY::RBTN))
	{
		HHKeyMgr::GetInstance()->MouseCapture(false);
	}
}

void HHCameraMoveScript::SaveToFile(FILE* _File)
{
	fwrite(&m_CamSpeed, sizeof(float), 1, _File);
}

void HHCameraMoveScript::LoadFromFile(FILE* _File)
{
	fread(&m_CamSpeed, sizeof(float), 1, _File);
}
