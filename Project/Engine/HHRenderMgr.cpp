#include "pch.h"
#include "HHRenderMgr.h"

#include "HHDevice.h"
#include "HHConstantBuffer.h"

#include "HHCamera.h"
#include "HHTimeMgr.h"
#include "HHAssetMgr.h"

#include "HHGameObject.h"
#include "HHTransform.h"
#include "HHMeshRender.h"

#include "HHLevelMgr.h"
#include "HHLevel.h"

#include "HHLight2D.h"
#include "HHStructuredBuffer.h"

#include "HHKeyMgr.h"

HHRenderMgr::HHRenderMgr()
	: m_EditorCamera(nullptr)
	, m_DebugObject(nullptr)
	, m_Light2DBuffer(nullptr)
{
	m_Light2DBuffer = new HHStructuredBuffer;
}

HHRenderMgr::~HHRenderMgr()
{
	if (nullptr != m_DebugObject)
		delete m_DebugObject;

	if (nullptr != m_Light2DBuffer)
		delete m_Light2DBuffer;
}

void HHRenderMgr::Initialize()
{
	// AssetMgr 가 초기화될때 만들어둔 후처리용 텍스쳐를 참조한다.
	m_PostProcessTex = HHAssetMgr::GetInstance()->FindAsset<HHTexture>(L"PostProcessTex");

	// 디버그 렌더링용 게임 오브젝트
	m_DebugObject = new HHGameObject;
	m_DebugObject->AddComponent(new HHTransform);
	m_DebugObject->AddComponent(new HHMeshRender);
	m_DebugObject->MeshRender()->SetMaterial(HHAssetMgr::GetInstance()->FindAsset<HHMaterial>(L"DebugShapeMtrl"));
}

void HHRenderMgr::Tick()
{
	HHLevel* pCurLevel = HHLevelMgr::GetInstance()->GetCurrentLevel();
	if (nullptr == pCurLevel)
		return;

	RenderStart();

	// Level 이 Player 상태인 경우, Level 내에 있는 카메라 시점으로 렌더링하기
	if (PLAY == pCurLevel->GetState())
	{
		for (size_t i = 0; i < m_vecCam.size(); ++i)
		{
			if (nullptr == m_vecCam[i])
				continue;

			m_vecCam[i]->Render();
		}
	}

	// Level 이 Stop 이나 Pause 인 경우, Editor 용 카메라 시점으로 렌더링 하기
	else
	{
		if (nullptr != m_EditorCamera)
		{
			m_EditorCamera->Render();
		}
	}

	// Debug Render
	RenderDebugShape();

	// Time 정보 출력
	HHTimeMgr::GetInstance()->Render();

	// Clear
	Clear();
}

void HHRenderMgr::RegisterCamera(HHCamera* _Cam, int _CamPriority)
{
	// 카메라 우선순위에 따라서 벡터의 공간의 마련되어야 한다.
	if (m_vecCam.size() <= _CamPriority + 1)
		m_vecCam.resize(_CamPriority + 1);

	// 카메라 우선순위에 맞는 위치에 넣는다
	m_vecCam[_CamPriority] = _Cam;
}

void HHRenderMgr::PostProcessCopy()
{
	// RenderTarget -> PostProcessTex
	Ptr<HHTexture> pRTTex = HHAssetMgr::GetInstance()->FindAsset<HHTexture>(L"RenderTargetTex");
	CONTEXT->CopyResource(m_PostProcessTex->GetTex2D().Get(), pRTTex->GetTex2D().Get());
}

void HHRenderMgr::RenderStart()
{
	// 렌더타겟 지정
	Ptr<HHTexture> pRTTex = HHAssetMgr::GetInstance()->FindAsset<HHTexture>(L"RenderTargetTex");
	Ptr<HHTexture> pDSTex = HHAssetMgr::GetInstance()->FindAsset<HHTexture>(L"DepthStencilTex");
	CONTEXT->OMSetRenderTargets(1, pRTTex->GetRTV().GetAddressOf(), pDSTex->GetDSV().Get());

	// TargetClear
	float color[4] = { 0.f, 0.f, 0.f, 1.f };
	CONTEXT->ClearRenderTargetView(pRTTex->GetRTV().Get(), color);
	CONTEXT->ClearDepthStencilView(pDSTex->GetDSV().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);

	g_GlobalData.g_Resolution = Vec2((float)pRTTex->Width(), (float)pRTTex->Height());
	g_GlobalData.g_Light2DCount = (int)m_vecLight2D.size();

	// Light2D 정보 업데이트 및 바인딩
	vector<tLightInfo> vecLight2DInfo;
	for (size_t i = 0; i < m_vecLight2D.size(); ++i)
	{
		vecLight2DInfo.push_back(m_vecLight2D[i]->GetLightInfo());
	}

	if (m_Light2DBuffer->GetElementCount() < vecLight2DInfo.size())
	{
		m_Light2DBuffer->Create(sizeof(tLightInfo), (UINT)vecLight2DInfo.size(), SB_TYPE::SRV_ONLY, true);
	}

	m_Light2DBuffer->SetData(vecLight2DInfo.data());
	m_Light2DBuffer->Binding(11);

	// GlobalData 바인딩
	static HHConstantBuffer* pGlobalCB = HHDevice::GetInstance()->GetConstantBuffer(CONSTANT_BUFFER_TYPE::GLOBAL);
	pGlobalCB->SetData(&g_GlobalData);
	pGlobalCB->Binding();
}

void HHRenderMgr::Clear()
{
	m_vecLight2D.clear();
}

void HHRenderMgr::RenderDebugShape()
{
	list<tDebugShapeInfo>::iterator iter = m_DebugShapeList.begin();

	for (; iter != m_DebugShapeList.end(); )
	{
		// 디버그 요청 모양에 맞는 메시를 가져옴
		switch ((*iter).Shape)
		{
		case DEBUG_SHAPE::RECT:
			m_DebugObject->MeshRender()->SetMesh(HHAssetMgr::GetInstance()->FindAsset<HHMesh>(L"RectMesh_Debug"));
			break;
		case DEBUG_SHAPE::CIRCLE:
			m_DebugObject->MeshRender()->SetMesh(HHAssetMgr::GetInstance()->FindAsset<HHMesh>(L"CircleMesh_Debug"));
			break;
		case DEBUG_SHAPE::LINE:

			break;
		case DEBUG_SHAPE::CUBE:

			break;
		case DEBUG_SHAPE::SPHERE:

			break;
		}

		// 위치 세팅
		m_DebugObject->Transform()->SetWorldMatrix((*iter).matWorld);

		// 재질 세팅
		m_DebugObject->MeshRender()->GetMaterial()->SetScalarParam(VEC4_0, (*iter).vColor);

		// 깊이판정 여부에 따라서, 쉐이더의 깊이판정 방식을 결정한다.
		if ((*iter).DepthTest)
			m_DebugObject->MeshRender()->GetMaterial()->GetShader()->SetDepthStencilType(DEPTH_STENCIL_STATE_TYPE::LESS);
		else
			m_DebugObject->MeshRender()->GetMaterial()->GetShader()->SetDepthStencilType(DEPTH_STENCIL_STATE_TYPE::NO_TEST_NO_WRITE);

		// 렌더링
		m_DebugObject->MeshRender()->Render();


		// 수명이 다한 디버그 정보를 삭제
		(*iter).Age += ENGINE_DT;
		if ((*iter).LifeTime < (*iter).Age)
		{
			iter = m_DebugShapeList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}
