#pragma once
#include "HHComponent.h"

#include "HHFSM.h"
#include "HHBlackboard.h"

class HHStateMachine :
    public HHComponent
{
public:
    CLONE(HHStateMachine);
    HHStateMachine();

    ~HHStateMachine();

    virtual void Begin() override;
    virtual void FinalTick() override;

    void SetFSM(Ptr<HHFSM> _FSM);
    Ptr<HHFSM> GetFSM()
    {
        if (m_FSM_Inst.Get())
            return m_FSM_Inst;
        else
            m_FSM;
    };

    void AddBlackboardData(const wstring& _strKey, BB_DATA _Type, void* _pData);
    void* GetBlackboardData(const wstring& _strKey);

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

private:
    Ptr<HHFSM>       m_FSM;
    Ptr<HHFSM>       m_FSM_Inst;

    HHBlackboard     m_Blackboard;

};
