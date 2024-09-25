#include "pch.h"
#include "HHCamera.h"

#include "HHDevice.h"

#include "HHRenderMgr.h"

#include "HHLevelMgr.h"
#include "HHLevel.h"
#include "HHLayer.h"
#include "HHGameObject.h"

#include "HHTimeMgr.h"
#include "HHKeyMgr.h"
#include "HHTransform.h"

#include "HHRenderComponent.h"

HHCamera::HHCamera()
	: HHComponent(COMPONENT_TYPE::CAMERA)
	, m_Priority(-1)
	, m_LayerCheck(0)
	, m_ProjectionType(PROJECTION_TYPE::ORTHOGRAPHIC)
	, m_Width(0)
	, m_Height(0)
	, m_Far(100000.f)
	, m_FOV(XM_PI / 2.f)
	, m_ProjectionScale(1.f)
	, m_TargetObject(nullptr)
{
	Vec2 vResolution = HHDevice::GetInstance()->GetResolution();
	m_Width = vResolution.x;
	m_Height = vResolution.y;
	m_AspectRatio = m_Width / m_Height;
}

HHCamera::~HHCamera()
{
}

void HHCamera::Begin()
{
	// 카메라를 등록
	if (-1 != m_Priority)
	{
		HHRenderMgr::GetInstance()->RegisterCamera(this, m_Priority);
	}
}

void HHCamera::FinalTick()
{
	/*Vec3 vWorldPos = Transform()->GetRelativePos();

	if (KEY_PRESSED(KEY::LEFT))
		vWorldPos.x -= DT * 1.f;
	if(KEY_PRESSED(KEY::RIGHT))
		vWorldPos.x += DT * 1.f;

	Transform()->SetRelativePos(vWorldPos);*/

	// View Space 란 카메라가 좌표계의 기준이 되는 좌표계
	// 1. 카메라가 원점에 존재
	// 2. 카메라가 바라보는 방향이 Z 축

	// 1. 카메라가 있는 곳이 원점이었을 경우를 기준으로한 물체들의 좌표를 알아내야 한다.
	// 2. 카메라가 월드에서 바라보던 방향을 Z 축으로 돌려두어야 한다.
	//    물체들도 같이 회전을 한다.

	// View 행렬을 계산한다.
	// View 행렬은 World Space -> View Space 로 변경할때 사용하는 행렬		

	if (m_TargetObject)
	{
		// Get the target's position
		Vec3 targetPosition = m_TargetObject->Transform()->GetWorldPosition();

		// Get the current camera position
		Vec3 cameraPosition = Transform()->GetRelativePosition();

		// Update the camera's position to follow the target's X and Y, but keep the Z unchanged
		cameraPosition.x = targetPosition.x;
		cameraPosition.y = targetPosition.y;

		// Set the camera's position
		Transform()->SetRelativePosition(cameraPosition);
	}

	Matrix matTrans = XMMatrixTranslation(-Transform()->GetRelativePosition().x
										, -Transform()->GetRelativePosition().y
										, -Transform()->GetRelativePosition().z);

	Matrix matRot;
	Vec3 vR = Transform()->GetWorldDirection(DIRECTION_TYPE::RIGHT);
	Vec3 vU = Transform()->GetWorldDirection(DIRECTION_TYPE::UP);
	Vec3 vF = Transform()->GetWorldDirection(DIRECTION_TYPE::FRONT);

	matRot._11 = vR.x; matRot._12 = vU.x; matRot._13 = vF.x;
	matRot._21 = vR.y; matRot._22 = vU.y; matRot._23 = vF.y;
	matRot._31 = vR.z; matRot._32 = vU.z; matRot._33 = vF.z;

	m_matView = matTrans * matRot;

	// Projection Space 투영 좌표계 (NDC)
	if (PROJECTION_TYPE::ORTHOGRAPHIC == m_ProjectionType)
	{
		// 1. 직교투영 (Orthographic)
		// 투영을 일직선으로
		// 시야 범위를 NDC 로 압축
		m_matProjection = XMMatrixOrthographicLH(m_Width * m_ProjectionScale, m_Height * m_ProjectionScale, 1.f, m_Far);
	}
	else
	{
		// 2. 원근투영 (Perspective)
		m_matProjection = XMMatrixPerspectiveFovLH(m_FOV, m_AspectRatio, 1.f, m_Far);
	}
}

void HHCamera::SortGameObject()
{
	HHLevel* pLevel = HHLevelMgr::GetInstance()->GetCurrentLevel();

	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		if (false == (m_LayerCheck & (1 << i)))
			continue;

		HHLayer* pLayer = pLevel->GetLayer(i);

		const vector<HHGameObject*>& vecObjects = pLayer->GetObjects();

		for (size_t j = 0; j < vecObjects.size(); ++j)
		{
			HHRenderComponent* pRenderComponent = vecObjects[j]->GetRenderComponent();

			if (pRenderComponent == nullptr)
				continue;

			Ptr<HHGraphicShader> pShader = vecObjects[j]->GetRenderComponent()->GetMaterial()->GetShader();

			SHADER_DOMAIN Domain = pShader->GetDomain();

			// Sort by Domain
			m_DomainSort[(UINT)Domain].push_back(vecObjects[j]);
		}
	}
}

void HHCamera::Render()
{
	// 오브젝트 분류
	SortGameObject();

	// 물체가 렌더링될 때 사용할 View, Proj 행렬
	g_Trans.matView = m_matView;
	g_Trans.matProjection = m_matProjection;

	for (int _idx = 0; _idx < (UINT)SHADER_DOMAIN::DOMAIN_NONE; _idx++)
	{
		if (_idx == (UINT)SHADER_DOMAIN::DOMAIN_POSTPROCESS)
		{
			PostProcessRender(m_DomainSort[_idx]);
		}
		else
		{
			Render(m_DomainSort[_idx]);
		}
	}
}

void HHCamera::Render(vector<HHGameObject*>& _vecObj)
{
	for (size_t _idx = 0; _idx < _vecObj.size(); _idx++)
	{
		_vecObj[_idx]->Render();
	}
	_vecObj.clear();
}

void HHCamera::PostProcessRender(vector<HHGameObject*>& _vecObj)
{
	for (size_t _idx = 0; _idx < _vecObj.size(); _idx++)
	{
		Ptr<HHTexture> pPostProcessTex = HHRenderMgr::GetInstance()->GetPostProcessTexture();
		pPostProcessTex->Binding(13);

		_vecObj[_idx]->Render();
	}
	_vecObj.clear();
}

void HHCamera::SaveToFile(FILE* _File)
{
	fwrite(&m_Priority, sizeof(int), 1, _File);
	fwrite(&m_LayerCheck, sizeof(UINT), 1, _File);
	fwrite(&m_ProjectionType, sizeof(PROJECTION_TYPE), 1, _File);
	fwrite(&m_Width, sizeof(float), 1, _File);
	fwrite(&m_Height, sizeof(float), 1, _File);
	fwrite(&m_AspectRatio, sizeof(float), 1, _File);
	fwrite(&m_Far, sizeof(float), 1, _File);
	fwrite(&m_FOV, sizeof(float), 1, _File);
	fwrite(&m_ProjectionScale, sizeof(float), 1, _File);
}

void HHCamera::LoadFromFile(FILE* _File)
{
	fread(&m_Priority, sizeof(int), 1, _File);
	fread(&m_LayerCheck, sizeof(UINT), 1, _File);
	fread(&m_ProjectionType, sizeof(PROJECTION_TYPE), 1, _File);
	fread(&m_Width, sizeof(float), 1, _File);
	fread(&m_Height, sizeof(float), 1, _File);
	fread(&m_AspectRatio, sizeof(float), 1, _File);
	fread(&m_Far, sizeof(float), 1, _File);
	fread(&m_FOV, sizeof(float), 1, _File);
	fread(&m_ProjectionScale, sizeof(float), 1, _File);
}
