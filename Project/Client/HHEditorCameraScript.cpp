#include "pch.h"
#include "HHEditorCameraScript.h"

HHEditorCameraScript::HHEditorCameraScript()
	: HHScript(-1)
	, m_Speed(500.f)
{
}

HHEditorCameraScript::~HHEditorCameraScript()
{
}

void HHEditorCameraScript::Tick()
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

void HHEditorCameraScript::OrthographicMovement()
{
	float Speed = m_Speed;

	if (KEY_PRESSED(KEY::LSHIFT))
	{
		Speed *= 3.f;
	}

	Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
	Vec3 vPos = Transform()->GetRelativePosition();

	if (KEY_PRESSED(KEY::W))
	{
		vPos.y += ENGINE_DT * Speed;
	}

	if (KEY_PRESSED(KEY::S))
	{
		vPos.y -= ENGINE_DT * Speed;
	}

	if (KEY_PRESSED(KEY::A))
	{
		vPos.x -= ENGINE_DT * Speed;
	}

	if (KEY_PRESSED(KEY::D))
	{
		vPos.x += ENGINE_DT * Speed;
	}

	Transform()->SetRelativePosition(vPos);

	float Scale = Camera()->GetScale();
	if (KEY_PRESSED(KEY::_8))
		Scale += ENGINE_DT;

	if (KEY_PRESSED(KEY::_9))
		Scale -= ENGINE_DT;

	Camera()->SetScale(Scale);
}

void HHEditorCameraScript::PerspectiveMovement()
{
	float Speed = m_Speed;

	if (KEY_PRESSED(KEY::LSHIFT))
	{
		Speed *= 3.f;
	}

	Vec3 vFront = Transform()->GetWorldDirection(DIRECTION_TYPE::FRONT);
	Vec3 vRight = Transform()->GetWorldDirection(DIRECTION_TYPE::RIGHT);

	Vec3 vPos = Transform()->GetRelativePosition();

	if (KEY_PRESSED(KEY::W))
	{
		vPos += vFront * ENGINE_DT * Speed;
	}

	if (KEY_PRESSED(KEY::S))
	{
		vPos -= vFront * ENGINE_DT * Speed;
	}

	if (KEY_PRESSED(KEY::A))
	{
		vPos -= vRight * ENGINE_DT * Speed;
	}

	if (KEY_PRESSED(KEY::D))
	{
		vPos += vRight * ENGINE_DT * Speed;
	}

	Transform()->SetRelativePosition(vPos);

	if (KEY_PRESSED(KEY::RBTN))
	{
		HHKeyMgr::GetInstance()->MouseCapture(true);

		// 마우스가 이동하는 방향
		//vDir.x; ==> y축 회전;
		//vDir.y; ==> x축 회전
		Vec2 vDir = HHKeyMgr::GetInstance()->GetDragDir();

		Vec3 vRot = Transform()->GetRelativeRoatation();
		vRot.y += vDir.x * XM_PI * ENGINE_DT * 10.f;
		vRot.x += vDir.y * XM_PI * ENGINE_DT * 10.f;
		Transform()->SetRelativeRotation(vRot);
	}
	else if (KEY_RELEASED(KEY::RBTN))
	{
		HHKeyMgr::GetInstance()->MouseCapture(false);
	}
}
