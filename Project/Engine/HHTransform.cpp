#include "pch.h"
#include "HHTransform.h"

#include "HHDevice.h"
#include "HHConstantBuffer.h"

HHTransform::HHTransform()
	: HHComponent(COMPONENT_TYPE::TRANSFORM)
	, m_RelativeDirection{}
	, m_WorldDirection{}
	, m_IndependentScale(false)
{
}

HHTransform::~HHTransform()
{
}

void HHTransform::FinalTick()
{
	// 오브젝트의 월드행렬 계산
	// 크기행렬
	Matrix matScale = XMMatrixScaling(m_RelativeScale.x, m_RelativeScale.y, m_RelativeScale.z);

	// 이동 행렬
	Matrix matTranslation = XMMatrixTranslation(m_RelativePosition.x, m_RelativePosition.y, m_RelativePosition.z);

	// 회전 행렬
	Matrix matRot = XMMatrixRotationX(m_RelativeRotation.x)
					* XMMatrixRotationY(m_RelativeRotation.y)
					* XMMatrixRotationZ(m_RelativeRotation.z);

	m_matWorld = matScale * matRot * matTranslation;

	// 방향벡터 계산
	static Vec3 vDefaultAxis[3] =
	{
		Vec3(1.f, 0.f, 0.f),
		Vec3(0.f, 1.f, 0.f),
		Vec3(0.f, 0.f, 1.f)
	};

	for (int i = 0; i < 3; ++i)
	{
		m_RelativeDirection[i] = XMVector3TransformNormal(vDefaultAxis[i], matRot);
		m_RelativeDirection[i].Normalize();
	}


	// 부모 오브젝트가 있는지 확인
	if (GetOwner()->GetParentObject())
	{
		// 부모의 월드행렬을 곱해서 최종 월드행렬을 계산함
		const Matrix& matParentWorldMat = GetOwner()->GetParentObject()->Transform()->GetWorldMatrix();

		if (m_IndependentScale)
		{
			Vec3 vParentScale = GetOwner()->GetParentObject()->Transform()->GetWorldScale();
			Matrix matParentScale = XMMatrixScaling(vParentScale.x, vParentScale.y, vParentScale.z);
			Matrix matParentScaceInv = XMMatrixInverse(nullptr, matParentScale);

			m_matWorld = m_matWorld * matParentScaceInv * matParentWorldMat;
		}
		else
		{
			m_matWorld *= matParentWorldMat;
		}

		// 최종 월드기준 오브젝트의 방향벡터를 구함
		for (int i = 0; i < 3; ++i)
		{
			m_WorldDirection[i] = XMVector3TransformNormal(vDefaultAxis[i], m_matWorld);
		}
	}

	// 부모가 없으면, RelativeDir 이 곧 WorldDir
	else
	{
		for (int i = 0; i < 3; ++i)
		{
			m_WorldDirection[i] = m_RelativeDirection[i];
		}
	}
}

void HHTransform::Binding()
{
	g_Trans.matWorld = m_matWorld;
	g_Trans.matWV = g_Trans.matWorld * g_Trans.matView;
	g_Trans.matWVP = g_Trans.matWV * g_Trans.matProjection;

	HHConstantBuffer* pTransformCB = HHDevice::GetInstance()->GetConstantBuffer(CONSTANT_BUFFER_TYPE::TRANSFORM);
	pTransformCB->SetData(&g_Trans);
	pTransformCB->Binding();
}

Vec3 HHTransform::GetWorldScale()
{
	Vec3 vWorldScale = Vec3(1.f, 1.f, 1.f);

	HHGameObject* pObject = GetOwner();

	while (pObject)
	{
		vWorldScale *= pObject->Transform()->GetRelativeScale();

		if (pObject->Transform()->m_IndependentScale)
			break;

		pObject = pObject->GetParentObject();
	}

	return vWorldScale;
}

void HHTransform::SaveToFile(FILE* _File)
{
	fwrite(&m_RelativePosition, sizeof(Vec3), 1, _File);
	fwrite(&m_RelativeScale, sizeof(Vec3), 1, _File);
	fwrite(&m_RelativeRotation, sizeof(Vec3), 1, _File);
	fwrite(&m_IndependentScale, sizeof(bool), 1, _File);
}

void HHTransform::LoadFromFile(FILE* _File)
{
	fread(&m_RelativePosition, sizeof(Vec3), 1, _File);
	fread(&m_RelativeScale, sizeof(Vec3), 1, _File);
	fread(&m_RelativeRotation, sizeof(Vec3), 1, _File);
	fread(&m_IndependentScale, sizeof(bool), 1, _File);
}
