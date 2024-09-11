#pragma once
#include "HHEntity.h"

class HHFSM;
class HHStateMachine;

class HHState :
    public HHEntity
{
    CLONE_DISABLE(HHState);
public:

    HHState();
    ~HHState();

    friend class HHFSM;

    virtual void FinalTick() = 0;
    virtual void Enter() = 0;
    virtual void Exit() = 0;

private:
    HHFSM* m_FSM;

protected:
    void* GetBlackboardData(const wstring& _strKey);
    HHFSM* GetFSM() { return m_FSM; }

    void ChangeState(const wstring& _strStateName);

};
