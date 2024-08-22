#include "pch.h"
#include "HHTaskMgr.h"

#include "HHLevelMgr.h"
#include "HHLevel.h"
#include "HHLayer.h"
#include "HHGameObject.h"

#include "HHAssetMgr.h"

HHTaskMgr::HHTaskMgr()
{}

HHTaskMgr::~HHTaskMgr()
{}

void HHTaskMgr::Tick()
{
	ClearGarbageCollector();

	ExecuteTask();
}

void HHTaskMgr::AddTask(const tTask& _Task)
{
	m_vecTask.push_back(_Task);
}

void HHTaskMgr::ClearGarbageCollector()
{
	Delete_Vec(m_GC);
}

void HHTaskMgr::ExecuteTask()
{
	for (size_t i = 0; i < m_vecTask.size(); ++i)
	{
		tTask& task = m_vecTask[i];
		switch (task.Type)
		{
		case TASK_TYPE::CREATE_OBJECT:
		{
			HHLevel* pCurLevel = HHLevelMgr::GetInstance()->GetCurrentLevel();
			int LayerIndex = (int)task.Param_0;
			HHGameObject* pObject = (HHGameObject*)task.Param_1;
			pCurLevel->AddObject(LayerIndex, pObject);

			if (pCurLevel->GetState() != STOP)
			{
				pObject->Begin();
			}
		}
		break;
		case TASK_TYPE::DELETE_OBJECT:
		{
			HHGameObject* pObject = (HHGameObject*)task.Param_0;
			if (pObject->m_Dead)
			{
				continue;
			}

			// GC 에서 수거
			pObject->m_Dead = true;
			m_GC.push_back(pObject);
		}
		break;
		case TASK_TYPE::CHANGE_LEVEL_STATE:
		{
			LEVEL_STATE NextState = (LEVEL_STATE)task.Param_0;
			HHLevel* pCurLevel = HHLevelMgr::GetInstance()->GetCurrentLevel();
			pCurLevel->ChangeState(NextState);
		}
		break;
		case TASK_TYPE::CHANGE_LEVEL:
		{
			// Param_0 : Level Adress, Param_1 : Level State
			HHLevel* pLevel = (HHLevel*)task.Param_0;
			LEVEL_STATE NextState = (LEVEL_STATE)task.Param_1;

			HHLevelMgr::GetInstance()->ChangeLevel(pLevel);
			pLevel->ChangeState(NextState);
		}
		break;
		case TASK_TYPE::LEVEL_CHANGED:
		{
			HHLevelMgr::GetInstance()->m_LevelChanged = true;
		}
		case TASK_TYPE::ASSET_CHANGED:
		{
			HHAssetMgr::GetInstance()->m_Changed = true;
		}
		break;

		case TASK_TYPE::DELETE_ASSET:
		{
			HHAsset* pAsset = (HHAsset*)task.Param_0;
			ASSET_TYPE Type = pAsset->GetAssetType();
			HHAssetMgr::GetInstance()->DeleteAsset(Type, pAsset->GetKey());
		}
		break;
		}
	}

	m_vecTask.clear();
}
