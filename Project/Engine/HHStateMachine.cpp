#include "pch.h"
#include "HHStateMachine.h"

HHStateMachine::HHStateMachine()
	: HHComponent(COMPONENT_TYPE::STATE_MACHINE)
{
}

HHStateMachine::~HHStateMachine()
{
}


void HHStateMachine::Begin()
{
	// 원본 FSM 에셋의 Instance 를 생성해둔다.
	if (m_FSM.Get())
	{
		m_FSM_Inst = m_FSM->GetFSMIstance();
		m_FSM_Inst->SetStateMachine(this);
	}
}

void HHStateMachine::FinalTick()
{
	if (m_FSM_Inst.Get())
		m_FSM_Inst->FinalTick();
}

void HHStateMachine::SetFSM(Ptr<HHFSM> _FSM)
{
	m_FSM = _FSM;
	m_FSM_Inst = nullptr;
}

void HHStateMachine::AddBlackboardData(const wstring& _strKey, BB_DATA _Type, void* _pData)
{
	m_Blackboard.AddBlackboardData(_strKey, _Type, _pData);
}

void* HHStateMachine::GetBlackboardData(const wstring& _strKey)
{
	return m_Blackboard.GetBlackboardData(_strKey);
}

void HHStateMachine::SaveToFile(FILE* _File)
{
}

void HHStateMachine::LoadFromFile(FILE* _File)
{
}
