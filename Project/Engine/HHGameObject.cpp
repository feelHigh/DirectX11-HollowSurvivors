#include "pch.h"
#include "HHGameObject.h"

#include "HHTimeMgr.h"
#include "HHKeyMgr.h"

#include "HHLevelMgr.h"
#include "HHLevel.h"
#include "HHLayer.h"

#include "components.h"
#include "HHScript.h"

HHGameObject::HHGameObject()
	: m_arrCom{}
	, m_RenderCom(nullptr)
	, m_ParentObj(nullptr)
	, m_LayerIdx(-1)		// -1: 모든 레이어 소속하지 않음(레벨에 있지 않은 상태)
	, m_Dead(false)
{
}

HHGameObject::HHGameObject(const HHGameObject& _Origin)
	: HHEntity(_Origin)
	, m_arrCom{}
	, m_RenderCom(nullptr)
	, m_ParentObj(nullptr)
	, m_LayerIdx(-1)
	, m_Dead(false)
{
	// 컴포넌트 복사
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr == _Origin.m_arrCom[i])
			continue;

		HHComponent* pClonedCom = _Origin.m_arrCom[i]->Clone();

		AddComponent(pClonedCom);

		pClonedCom->Initialize();
	}

	// Script 복사
	for (size_t i = 0; i < _Origin.m_vecScript.size(); ++i)
	{
		AddComponent(_Origin.m_vecScript[i]->Clone());
	}

	// 자식 오브젝트 복사
	for (size_t i = 0; i < _Origin.m_vecChildObj.size(); ++i)
	{
		AddChild(_Origin.m_vecChildObj[i]->Clone());
	}
}

HHGameObject::~HHGameObject()
{
	Delete_Array(m_arrCom);
	Delete_Vec(m_vecScript);
	Delete_Vec(m_vecChildObj);
}

void HHGameObject::AddComponent(HHComponent* _Component)
{
	COMPONENT_TYPE Type = _Component->GetComponentType();

	if (COMPONENT_TYPE::SCRIPT == Type)
	{
		m_vecScript.push_back((HHScript*)_Component);
		_Component->SetOwner(this);
	}
	else
	{
		assert(nullptr == m_arrCom[(UINT)Type]);

		m_arrCom[(UINT)Type] = _Component;
		m_arrCom[(UINT)Type]->SetOwner(this);

		HHRenderComponent* pRenderCom = dynamic_cast<HHRenderComponent*>(_Component);

		assert(!(pRenderCom && m_RenderCom));

		if (pRenderCom)
		{
			m_RenderCom = pRenderCom;
		}
	}
}

void HHGameObject::AddChild(HHGameObject* _ChildObject)
{
	// 부모 오브젝트는 Level 에 속해있고, AddChild 되는 자식 오브젝트는 레벨에 소속되지 않은 경우
	if (-1 != m_LayerIdx && -1 == _ChildObject->m_LayerIdx)
	{
		assert(nullptr);
	}

	// 자식으로 들어오는 오브젝트가 이미 부모가 있는 경우
	if (_ChildObject->GetParentObject())
	{
		_ChildObject->DeregisterChild();
	}

	// 자식으로 들어오는 오브젝트가 최상위 부모 오브젝트인 경우
	else
	{
		if (-1 != _ChildObject->m_LayerIdx)
		{
			HHLevel* pCurLevel = HHLevelMgr::GetInstance()->GetCurrentLevel();
			if (nullptr != pCurLevel)
			{
				HHLayer* pLayer = pCurLevel->GetLayer(_ChildObject->m_LayerIdx);
				pLayer->DeregisterObjectAsParent(_ChildObject);
			}
		}
	}

	m_vecChildObj.push_back(_ChildObject);
	_ChildObject->m_ParentObj = this;

	HHLevelMgr::GetInstance()->LevelChanged();
}

bool HHGameObject::IsAncestor(HHGameObject* _Object)
{
	HHGameObject* pObject = m_ParentObj;

	while (pObject)
	{
		if (pObject == _Object)
			return true;
		else
			pObject = pObject->GetParentObject();
	}

	return false;
}

void HHGameObject::DisconnectWithLayer()
{
	if (nullptr == m_ParentObj)
	{
		HHLevel* pLevel = HHLevelMgr::GetInstance()->GetCurrentLevel();
		HHLayer* pLayer = pLevel->GetLayer(m_LayerIdx);
		pLayer->DisconnectWithObject(this);
	}

	m_LayerIdx = -1;
}

void HHGameObject::DeregisterChild()
{
	HHLevelMgr::GetInstance()->LevelChanged();

	vector<HHGameObject*>::iterator iter = m_ParentObj->m_vecChildObj.begin();

	for (; iter != m_ParentObj->m_vecChildObj.end(); ++iter)
	{
		if ((*iter) == this)
		{
			m_ParentObj->m_vecChildObj.erase(iter);
			m_ParentObj = nullptr;
			return;
		}
	}

	assert(nullptr);
}

void HHGameObject::Begin()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr == m_arrCom[i])
			continue;

		m_arrCom[i]->Begin();
	}

	for (size_t i = 0; i < m_vecScript.size(); ++i)
	{
		m_vecScript[i]->Begin();
	}

	// 자식 오브젝트
	for (size_t i = 0; i < m_vecChildObj.size(); ++i)
	{
		m_vecChildObj[i]->Begin();
	}
}

void HHGameObject::Tick()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->Tick();
	}

	for (size_t i = 0; i < m_vecScript.size(); ++i)
	{
		m_vecScript[i]->Tick();
	}

	// 자식 오브젝트
	for (size_t i = 0; i < m_vecChildObj.size(); ++i)
	{
		m_vecChildObj[i]->Tick();
	}
}

void HHGameObject::FinalTick()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->FinalTick();
	}

	// 레이어 등록
	assert(-1 != m_LayerIdx);
	HHLevel* pLevel = HHLevelMgr::GetInstance()->GetCurrentLevel();
	HHLayer* pLayer = pLevel->GetLayer(m_LayerIdx);
	pLayer->RegisterGameObject(this);

	// 자식 오브젝트
	vector<HHGameObject*>::iterator iter = m_vecChildObj.begin();
	for (; iter != m_vecChildObj.end(); )
	{
		(*iter)->FinalTick();

		if ((*iter)->IsDeadObject())
			iter = m_vecChildObj.erase(iter);
		else
			++iter;
	}
}

void HHGameObject::Render()
{
	if (m_RenderCom)
		m_RenderCom->Render();
}
