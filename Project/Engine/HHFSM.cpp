#include "pch.h"
#include "HHFSM.h"

HHFSM::HHFSM()
	: HHAsset(ASSET_TYPE::FSM)
	, m_Master(nullptr)
	, m_Blackboard(nullptr)
{
}

HHFSM::~HHFSM()
{
	if (m_Blackboard)
		delete m_Blackboard;

	if (!m_Master)
	{
		Delete_Map(m_mapState);
	}
}

void HHFSM::FinalTick()
{
	if (m_CurState)
	{
		m_CurState->m_FSM = this;
		m_CurState->FinalTick();
	}
}

void HHFSM::AddState(const wstring& _StateName, HHState* _State)
{
	assert(!(FindState(_StateName)));

	_State->m_FSM = this;
	m_mapState.insert(make_pair(_StateName, _State));
}

HHState* HHFSM::FindState(const wstring& _StateName)
{
	map<wstring, HHState*>::iterator iter = m_mapState.find(_StateName);

	if (iter == m_mapState.end())
		return nullptr;

	return iter->second;
}

void HHFSM::SetState(const wstring& _strState)
{
	m_CurState = FindState(_strState);
}

HHFSM* HHFSM::GetFSMIstance()
{
	HHFSM* pFSMInst = new HHFSM();

	pFSMInst->m_mapState = m_mapState;
	pFSMInst->m_Master = this;
	pFSMInst->m_Blackboard = nullptr;
	pFSMInst->m_CurState = nullptr;

	return pFSMInst;
}

void HHFSM::ChangeState(const wstring& _strStateName)
{
	if (nullptr != m_CurState)
		m_CurState->Exit();

	m_CurState = FindState(_strStateName);

	assert(m_CurState);

	m_CurState->Enter();
}

int HHFSM::Load(const wstring& _FilePath)
{
	return 0;
}

int HHFSM::Save(const wstring& _FilePath)
{
	return 0;
}
