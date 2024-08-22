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
	, m_LayerIdx(-1)		// -1: ��� ���̾� �Ҽ����� ����(������ ���� ���� ����)
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
	// ������Ʈ ����
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr == _Origin.m_arrCom[i])
			continue;

		HHComponent* pClonedCom = _Origin.m_arrCom[i]->Clone();

		AddComponent(pClonedCom);

		pClonedCom->Initialize();
	}

	// Script ����
	for (size_t i = 0; i < _Origin.m_vecScript.size(); ++i)
	{
		AddComponent(_Origin.m_vecScript[i]->Clone());
	}

	// �ڽ� ������Ʈ ����
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
	// �θ� ������Ʈ�� Level �� �����ְ�, AddChild �Ǵ� �ڽ� ������Ʈ�� ������ �Ҽӵ��� ���� ���
	if (-1 != m_LayerIdx && -1 == _ChildObject->m_LayerIdx)
	{
		assert(nullptr);
	}

	// �ڽ����� ������ ������Ʈ�� �̹� �θ� �ִ� ���
	if (_ChildObject->GetParentObject())
	{
		_ChildObject->DeregisterChild();
	}

	// �ڽ����� ������ ������Ʈ�� �ֻ��� �θ� ������Ʈ�� ���
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

	// �ڽ� ������Ʈ
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

	// �ڽ� ������Ʈ
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

	// ���̾� ���
	assert(-1 != m_LayerIdx);
	HHLevel* pLevel = HHLevelMgr::GetInstance()->GetCurrentLevel();
	HHLayer* pLayer = pLevel->GetLayer(m_LayerIdx);
	pLayer->RegisterGameObject(this);

	// �ڽ� ������Ʈ
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
