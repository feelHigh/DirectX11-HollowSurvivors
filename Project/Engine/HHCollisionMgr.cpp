#include "pch.h"
#include "HHCollisionMgr.h"

#include "HHLevelMgr.h"
#include "HHLevel.h"
#include "HHLayer.h"
#include "HHGameObject.h"
#include "HHCollider2D.h"

#include "HHAssetMgr.h"

HHCollisionMgr::HHCollisionMgr()
	: m_Matrix{}
{
}

HHCollisionMgr::~HHCollisionMgr()
{
}

void HHCollisionMgr::Tick()
{
	for (int Row = 0; Row < MAX_LAYER; ++Row)
	{
		for (int Col = Row; Col < MAX_LAYER; ++Col)
		{
			if (m_Matrix[Row] & (1 << Col))
			{
				CollisionBetweenLayer(Row, Col);
			}
		}
	}
}

void HHCollisionMgr::CollisionCheck(UINT Layer1, UINT Layer2)
{
	UINT Row = Layer1;
	UINT Col = Layer2;

	if (Row > Col)
	{
		Row = (UINT)Layer2;
		Col = (UINT)Layer1;
	}

	if (m_Matrix[Row] & (1 << Col))
	{
		m_Matrix[Row] &= ~(1 << Col);
	}
	else
	{
		m_Matrix[Row] |= (1 << Col);
	}
}

void HHCollisionMgr::CollisionBetweenLayer(UINT _Left, UINT _Right)
{
	// 현재 레벨 가져온다.
	HHLevel* pCurLevel = HHLevelMgr::GetInstance()->GetCurrentLevel();
	if (nullptr == pCurLevel)
		return;

	// 각 레이어에 속한 모든 오브젝트들을 가져온다.
	const vector<HHGameObject*>& vecLeft = pCurLevel->GetLayer(_Left)->GetObjects();
	const vector<HHGameObject*>& vecRight = pCurLevel->GetLayer(_Right)->GetObjects();

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		HHCollider2D* pLeftCol = vecLeft[i]->Collider2D();
		if (nullptr == pLeftCol)
			continue;

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			HHCollider2D* pRightCol = vecRight[j]->Collider2D();
			if (nullptr == pRightCol)
				continue;

			COLLIDER_ID id = {};

			id.LeftID = pLeftCol->GetID();
			id.RightID = pRightCol->GetID();

			map<ULONGLONG, bool>::iterator iter = m_mapCollisionInfo.find(id.ID);

			// 등록된적이 없으면 등록시킨다.
			if (iter == m_mapCollisionInfo.end())
			{
				m_mapCollisionInfo.insert(make_pair(id.ID, false));
				iter = m_mapCollisionInfo.find(id.ID);
			}

			bool bDead = pLeftCol->GetOwner()->IsDeadObject() || pRightCol->GetOwner()->IsDeadObject();
			//bool bDeactive = !vecLeft[i]->IsActive() || !vecRight[j]->IsActive();

			// 두 충돌체가 지금 충돌중이다.
			if (IsCollision(pLeftCol, pRightCol))
			{
				// 이전에도 충돌중이었다.
				if (iter->second)
				{
					pLeftCol->Overlap(pRightCol);
					pRightCol->Overlap(pLeftCol);
				}

				// 이전에는 충돌중이 아니었다.
				else
				{
					pLeftCol->BeginOverlap(pRightCol);
					pRightCol->BeginOverlap(pLeftCol);
				}

				iter->second = true;

				// 두 충돌체중 하나라도 Dead 상태거나 비활성화 상태라면
				// 추가로 충돌 해제를 호출시켜준다.
				if (bDead)//|| bDeactive)
				{
					pLeftCol->EndOverlap(pRightCol);
					pRightCol->EndOverlap(pLeftCol);
					iter->second = false;
				}
			}

			// 두 충돌체가 지금 충돌중이 아니다.
			else
			{
				// 이전에는 충돌중이었다.
				if (iter->second)
				{
					pLeftCol->EndOverlap(pRightCol);
					pRightCol->EndOverlap(pLeftCol);
				}

				iter->second = false;
			}
		}
	}
}

bool HHCollisionMgr::IsCollision(HHCollider2D* _Left, HHCollider2D* _Right)
{
	// 충돌체의 기본 원형 도형을 가져온다.
	Ptr<HHMesh> pRectMesh = HHAssetMgr::GetInstance()->FindAsset<HHMesh>(L"RectMesh");
	Vtx* pVtx = (Vtx*)pRectMesh->GetVertexSystemMemory();

	// 각 충돌체의 월드 행렬을 가져온다.
	const Matrix& matLeft = _Left->GetWorldMatrix();
	const Matrix& matRight = _Right->GetWorldMatrix();

	// 기본 도형(Rect) 를 각 충돌체의 월드행렬을 곱해서, 충돌체의 각 모서리 위치로 옮긴 후,
	// 좌표끼리 위치값을 빼서 충돌체의 월드상에서의 위치에서 도형의 표면 방향벡터를 구한다.
	// 이 벡터는 충돌체들을 투영시킬 축이 될 예정
	Vec3 vProjAxis[4] = {};

	vProjAxis[0] = XMVector3TransformCoord(pVtx[3].vPosition, matLeft) - XMVector3TransformCoord(pVtx[0].vPosition, matLeft);
	vProjAxis[1] = XMVector3TransformCoord(pVtx[1].vPosition, matLeft) - XMVector3TransformCoord(pVtx[0].vPosition, matLeft);

	vProjAxis[2] = XMVector3TransformCoord(pVtx[3].vPosition, matRight) - XMVector3TransformCoord(pVtx[0].vPosition, matRight);
	vProjAxis[3] = XMVector3TransformCoord(pVtx[1].vPosition, matRight) - XMVector3TransformCoord(pVtx[0].vPosition, matRight);

	// 충돌체의 중심을 잇는 벡터
	Vec3 vCenter = XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), matLeft) - XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), matRight);

	// 투영
	for (int i = 0; i < 4; ++i)
	{
		Vec3 vProj = vProjAxis[i];
		vProj.Normalize();

		float dot = fabs(vProjAxis[0].Dot(vProj));
		dot += fabs(vProjAxis[1].Dot(vProj));
		dot += fabs(vProjAxis[2].Dot(vProj));
		dot += fabs(vProjAxis[3].Dot(vProj));
		dot /= 2.f;

		float fCenter = fabs(vCenter.Dot(vProj));

		if (dot < fCenter)
			return false;
	}

	return true;
}