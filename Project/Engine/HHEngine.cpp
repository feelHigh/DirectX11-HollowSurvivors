#include "pch.h"
#include "HHEngine.h"

#include "HHDevice.h"
#include "HHPathMgr.h"
#include "HHKeyMgr.h"
#include "HHTimeMgr.h"
#include "HHAssetMgr.h"
#include "HHLevelMgr.h"
#include "HHRenderMgr.h"
#include "HHCollisionMgr.h"
#include "HHTaskMgr.h"
#include "HHFontMgr.h"
#include "HHPrefab.h"

HHEngine::HHEngine()
	: m_hWnd(nullptr)
	, m_ptResolution{}
{
}

HHEngine::~HHEngine()
{
	if (nullptr != m_FMODSystem)
	{
		m_FMODSystem->release();
		m_FMODSystem = nullptr;
	}
}

int HHEngine::Initialize(HWND _wnd, POINT _ptResolution, OBJECT_SAVE _SaveFunc, OBJECT_LOAD _Func)
{
	m_hWnd = _wnd;
	m_ptResolution = _ptResolution;
	ChangeWindowScale(_ptResolution.x, _ptResolution.y);

	if (FAILED(HHDevice::GetInstance()->Initialize(m_hWnd, m_ptResolution.x, m_ptResolution.y)))
	{
		MessageBox(nullptr, L"장치 초기화 실패", L"HHDevice 초기화 실패", MB_OK);
		return E_FAIL;
	}

	// FMOD 초기화		
	FMOD::System_Create(&m_FMODSystem);
	assert(m_FMODSystem);

	// 32개 채널 생성
	m_FMODSystem->init(32, FMOD_DEFAULT, nullptr);

	// Manager 초기화
	HHPathMgr::GetInstance()->Initialize();
	HHKeyMgr::GetInstance()->Initialize();
	HHTimeMgr::GetInstance()->Initialize();
	HHAssetMgr::GetInstance()->Initialize();
	HHRenderMgr::GetInstance()->Initialize();
	HHLevelMgr::GetInstance()->Initialize();
	HHFontMgr::GetInstance()->Initialize();

	// Prefab Function 등록
	HHPrefab::g_ObjectSaveFunc = _SaveFunc;
	HHPrefab::g_ObjectLoadFunc = _Func;

	return S_OK;
}

void HHEngine::Progress()
{
	// FMOD Tick
	m_FMODSystem->update();

	// Manager
	HHKeyMgr::GetInstance()->Tick();
	HHTimeMgr::GetInstance()->Tick();
	HHAssetMgr::GetInstance()->Tick();
	HHLevelMgr::GetInstance()->Progress();

	// Collision
	HHCollisionMgr::GetInstance()->Tick();

	// Render
	HHRenderMgr::GetInstance()->Tick();

	// Task Manager
	HHTaskMgr::GetInstance()->Tick();
}

void HHEngine::ChangeWindowScale(UINT _Width, UINT _Height)
{
	bool bMenu = false;
	if (GetMenu(m_hWnd))
		bMenu = true;

	RECT rt = { 0, 0, (int)_Width, (int)_Height };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, bMenu);
	SetWindowPos(m_hWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
}
