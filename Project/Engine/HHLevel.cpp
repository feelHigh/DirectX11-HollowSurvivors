#include "pch.h"
#include "HHLevel.h"

#include "HHLevelMgr.h"

#include "HHLayer.h"
#include "HHGameObject.h"

HHLevel::HHLevel()
	: m_Layer{}
	, m_State(LEVEL_STATE::STOP)
{
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		m_Layer[i] = new HHLayer(i);
	}
}

HHLevel::HHLevel(const HHLevel& _Origin)
	: HHEntity(_Origin)
	, m_Layer{}
	, m_State(LEVEL_STATE::STOP)
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_Layer[i] = _Origin.m_Layer[i]->Clone();
	}
}

HHLevel::~HHLevel()
{
	Delete_Array(m_Layer);
}

void HHLevel::Begin()
{
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		m_Layer[i]->Begin();
	}
}

void HHLevel::Tick()
{
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		m_Layer[i]->Tick();
	}
}

void HHLevel::FinalTick()
{
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		m_Layer[i]->FinalTick();
	}
}

void HHLevel::AddObject(int LayerIdx, HHGameObject* _Object, bool _bMoveChild)
{
	m_Layer[LayerIdx]->AddObject(_Object, _bMoveChild);

	HHLevelMgr::GetInstance()->LevelChanged();
}

void HHLevel::RegisterAsParent(int LayerIdx, HHGameObject* _Object)
{
	m_Layer[LayerIdx]->RegisterAsParentLayer(_Object);
}

void HHLevel::ClearObject()
{
	for (UINT i = 0; i < MAX_LAYER; i++)
	{
		m_Layer[i]->ClearObject();
	}
}

HHGameObject* HHLevel::FindObjectByName(const wstring& _Name)
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		const vector<HHGameObject*>& vecParent = m_Layer[i]->GetParentObjects();

		static list<HHGameObject*> list;
		for (size_t i = 0; i < vecParent.size(); ++i)
		{
			list.clear();
			list.push_back(vecParent[i]);

			while (!list.empty())
			{
				HHGameObject* pObject = list.front();
				list.pop_front();

				const vector<HHGameObject*>& vecChild = pObject->GetChildObjects();
				for (size_t i = 0; i < vecChild.size(); ++i)
				{
					list.push_back(vecChild[i]);
				}

				if (_Name == pObject->GetName())
				{
					return pObject;
				}
			}
		}
	}

	return nullptr;
}

void HHLevel::ChangeState(LEVEL_STATE _NextState)
{
	if (m_State == _NextState)
		return;

	// Stop -> Pause (X)
	if (STOP == m_State && PAUSE == _NextState)
		return;

	// Stop -> Play (정지 상태의 레벨이 시작되면, 레벨에 있던 물체들은 Begin 이 호출되어야 한다.)
	if (STOP == m_State && PLAY == _NextState)
	{
		m_State = _NextState;
		Begin();
	}
	else
	{
		m_State = _NextState;
	}

	m_State = _NextState;

	// Play -> Stop (최초 레벨이 시작되던 시점으로 복구가 가능해야 한다.)
}
