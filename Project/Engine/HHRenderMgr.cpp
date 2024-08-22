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
	// AssetMgr �� �ʱ�ȭ�ɶ� ������ ��ó���� �ؽ��ĸ� �����Ѵ�.
	m_PostProcessTex = HHAssetMgr::GetInstance()->FindAsset<HHTexture>(L"PostProcessTex");

	// ����� �������� ���� ������Ʈ
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

	// Level �� Player ������ ���, Level ���� �ִ� ī�޶� �������� �������ϱ�
	if (PLAY == pCurLevel->GetState())
	{
		for (size_t i = 0; i < m_vecCam.size(); ++i)
		{
			if (nullptr == m_vecCam[i])
				continue;

			m_vecCam[i]->Render();
		}
	}

	// Level �� Stop �̳� Pause �� ���, Editor �� ī�޶� �������� ������ �ϱ�
	else
	{
		if (nullptr != m_EditorCamera)
		{
			m_EditorCamera->Render();
		}
	}

	// Debug Render
	RenderDebugShape();

	// Time ���� ���
	HHTimeMgr::GetInstance()->Render();

	// Clear
	Clear();
}

void HHRenderMgr::RegisterCamera(HHCamera* _Cam, int _CamPriority)
{
	// ī�޶� �켱������ ���� ������ ������ ���õǾ�� �Ѵ�.
	if (m_vecCam.size() <= _CamPriority + 1)
		m_vecCam.resize(_CamPriority + 1);

	// ī�޶� �켱������ �´� ��ġ�� �ִ´�
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
	// ����Ÿ�� ����
	Ptr<HHTexture> pRTTex = HHAssetMgr::GetInstance()->FindAsset<HHTexture>(L"RenderTargetTex");
	Ptr<HHTexture> pDSTex = HHAssetMgr::GetInstance()->FindAsset<HHTexture>(L"DepthStencilTex");
	CONTEXT->OMSetRenderTargets(1, pRTTex->GetRTV().GetAddressOf(), pDSTex->GetDSV().Get());

	// TargetClear
	float color[4] = { 0.f, 0.f, 0.f, 1.f };
	CONTEXT->ClearRenderTargetView(pRTTex->GetRTV().Get(), color);
	CONTEXT->ClearDepthStencilView(pDSTex->GetDSV().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);

	g_GlobalData.g_Resolution = Vec2((float)pRTTex->Width(), (float)pRTTex->Height());
	g_GlobalData.g_Light2DCount = (int)m_vecLight2D.size();

	// Light2D ���� ������Ʈ �� ���ε�
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

	// GlobalData ���ε�
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
		// ����� ��û ��翡 �´� �޽ø� ������
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

		// ��ġ ����
		m_DebugObject->Transform()->SetWorldMatrix((*iter).matWorld);

		// ���� ����
		m_DebugObject->MeshRender()->GetMaterial()->SetScalarParam(VEC4_0, (*iter).vColor);

		// �������� ���ο� ����, ���̴��� �������� ����� �����Ѵ�.
		if ((*iter).DepthTest)
			m_DebugObject->MeshRender()->GetMaterial()->GetShader()->SetDepthStencilType(DEPTH_STENCIL_STATE_TYPE::LESS);
		else
			m_DebugObject->MeshRender()->GetMaterial()->GetShader()->SetDepthStencilType(DEPTH_STENCIL_STATE_TYPE::NO_TEST_NO_WRITE);

		// ������
		m_DebugObject->MeshRender()->Render();


		// ������ ���� ����� ������ ����
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
