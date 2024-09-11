#pragma once
#include "HHAsset.h"

#include "HHState.h"
#include "HHBlackboard.h"

class HHStateMachine;

class HHFSM :
    public HHAsset
{
    CLONE_DISABLE(HHFSM);
public:
    HHFSM();
    ~HHFSM();

    void FinalTick();

    void AddState(const wstring& _StateName, HHState* _State);

    HHState* FindState(const wstring& _StateName);

    void SetState(const wstring& _strState);
    void SetStateMachine(HHStateMachine* _SM)
    {
        if (m_Master)
        {
            m_StateMachine = _SM;
        }
    }
    HHFSM* GetFSMIstance();

    HHStateMachine* GetStateMachine() { return m_StateMachine; }
    void ChangeState(const wstring& _strStateName);

    virtual int Load(const wstring& _FilePath) override;
    virtual int Save(const wstring& _FilePath) override;

private:
    HHFSM*                  m_Master;
    HHStateMachine*         m_StateMachine; // FSM 을 사용하는 StateMachine;

    map<wstring, HHState*>  m_mapState;
    HHBlackboard*           m_Blackboard;

    HHState*                m_CurState;

};
