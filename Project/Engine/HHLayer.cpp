#include "pch.h"
#include "HHLayer.h"
#include "HHGameObject.h"

HHLayer::HHLayer(int _LayerIdx)
	: m_LayerIdx(_LayerIdx)
{
}

HHLayer::HHLayer(const HHLayer& _Origin)
	: HHEntity(_Origin)
	, m_LayerIdx(_Origin.m_LayerIdx)
{
	for (size_t i = 0; i < _Origin.m_vecParentObj.size(); ++i)
	{
		AddObject(_Origin.m_vecParentObj[i]->Clone(), false);
	}
}

HHLayer::~HHLayer()
{
	Delete_Vec(m_vecParentObj);
}

void HHLayer::Begin()
{
	for (size_t i = 0; i < m_vecParentObj.size(); ++i)
	{
		m_vecParentObj[i]->Begin();
	}
}

void HHLayer::Tick()
{
	for (size_t i = 0; i < m_vecParentObj.size(); ++i)
	{
		m_vecParentObj[i]->Tick();
	}
}

void HHLayer::FinalTick()
{
	vector<HHGameObject*>::iterator iter = m_vecParentObj.begin();

	for (; iter != m_vecParentObj.end(); )
	{
		(*iter)->FinalTick();

		if ((*iter)->IsDeadObject())
			iter = m_vecParentObj.erase(iter);
		else
			++iter;
	}
}

void HHLayer::AddObject(HHGameObject* _Object, bool _bMoveChild)
{
	// 1. 오브젝트가 다른 레이어 소속인경우
	if (-1 != _Object->GetLayerIndex())
	{
		assert(_Object->GetLayerIndex() != m_LayerIdx);

		// 기존에 소속된 레이어에서 빠져나와야한다.
		_Object->DisconnectWithLayer();
	}

	// 2. 최상위 오브젝트인 경우
	if (nullptr == _Object->GetParentObject())
	{
		m_vecParentObj.push_back(_Object);
	}

	// 자식들까지 이동시킬지 말지
	static list<HHGameObject*> queue;
	queue.clear();
	queue.push_back(_Object);
	_Object->m_LayerIdx = m_LayerIdx;

	while (!queue.empty())
	{
		HHGameObject* pObject = queue.front();
		queue.pop_front();

		if (_bMoveChild || pObject->m_LayerIdx == -1)
		{
			pObject->m_LayerIdx = m_LayerIdx;
		}

		const vector<HHGameObject*>& vecChildren = pObject->GetChildObjects();
		for (size_t i = 0; i < vecChildren.size(); ++i)
		{
			queue.push_back(vecChildren[i]);
		}
	}
}

void HHLayer::DisconnectWithObject(HHGameObject* _Object)
{
	vector<HHGameObject*>::iterator iter = m_vecParentObj.begin();
	for (; iter != m_vecParentObj.end(); ++iter)
	{
		if (_Object == (*iter))
		{
			m_vecParentObj.erase(iter);
			return;
		}
	}

	assert(nullptr);
}

void HHLayer::RegisterAsParentLayer(HHGameObject* _Object)
{
	assert(_Object->GetLayerIndex() == m_LayerIdx && !_Object->GetParentObject());

	m_vecParentObj.push_back(_Object);
	return;
}

void HHLayer::DeregisterObjectAsParent(HHGameObject* _Object)
{
	vector<HHGameObject*>::iterator iter = m_vecParentObj.begin();

	for (; iter != m_vecParentObj.end(); ++iter)
	{
		if (_Object == (*iter))
		{
			m_vecParentObj.erase(iter);
			return;
		}
	}

	assert(nullptr);
}

void HHLayer::DeregisterObject(HHGameObject* _Object)
{
	assert(_Object->m_LayerIdx == m_LayerIdx);

	_Object->m_LayerIdx = -1;

	if (nullptr == _Object->GetParentObject())
	{
		vector<HHGameObject*>::iterator iter = m_vecParentObj.begin();

		for (; iter != m_vecParentObj.end(); ++iter)
		{
			if (_Object == (*iter))
			{
				m_vecParentObj.erase(iter);
				return;
			}
		}

		assert(nullptr);
	}
}
