#include "pch.h"
#include "HHLevelMgr.h"

#include "HHLevel.h"
#include "HHLayer.h"
#include "HHGameObject.h"

#include "HHTaskMgr.h"

HHLevelMgr::HHLevelMgr()
	: m_CurLevel(nullptr)
{

}

HHLevelMgr::~HHLevelMgr()
{
	if (nullptr != m_CurLevel)
		delete m_CurLevel;
}

void HHLevelMgr::LevelChanged()
{
	HHTaskMgr::GetInstance()->AddTask(tTask{ TASK_TYPE::LEVEL_CHANGED });
}

HHGameObject* HHLevelMgr::FindObjectByName(const wstring& _Name)
{
	if (m_CurLevel)
	{
		return m_CurLevel->FindObjectByName(_Name);
	}

	return nullptr;
}

void HHLevelMgr::Initialize()
{
	// 모든 레벨 생성
	/*
	m_arrLevel[(UINT)LEVEL_TYPE::TITLE] = new HHTestLevel;
	m_arrLevel[(UINT)LEVEL_TYPE::LEVEL_1] = new HHTestLevel2;


	// 초기 레벨 지정
	::ChangeLevel(LEVEL_TYPE::TITLE);
	*/
}

void HHLevelMgr::Progress()
{
	m_LevelChanged = false;
	if (nullptr == m_CurLevel)
		return;

	if (m_CurLevel->GetState() == LEVEL_STATE::PLAY)
	{
		m_CurLevel->Tick();
	}

	m_CurLevel->ClearObject();
	m_CurLevel->FinalTick();
}

bool HHLevelMgr::ChangeLevel(HHLevel* _NextLevel)
{
	if (m_CurLevel == _NextLevel)
		return false;

	if (nullptr != m_CurLevel)
		delete m_CurLevel;

	m_CurLevel = _NextLevel;

	// 레벨이 변경된 이벤트 ON
	LevelChanged();

	return true;
}
