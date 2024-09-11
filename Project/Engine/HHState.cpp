#include "pch.h"
#include "HHState.h"

#include "HHStateMachine.h"

HHState::HHState()
	: m_FSM(nullptr)
{
}

HHState::~HHState()
{
}

void* HHState::GetBlackboardData(const wstring& _strKey)
{
	HHStateMachine* pSM = m_FSM->GetStateMachine();
	return pSM->GetBlackboardData(_strKey);
}

void HHState::ChangeState(const wstring& _strStateName)
{
	assert(m_FSM);
	m_FSM->ChangeState(_strStateName);
}
