#pragma once
#include "HHEntity.h"

class HHLayer;
class HHGameObject;

class HHLevel :
    public HHEntity
{
public:
    CLONE(HHLevel);
    HHLevel();
    HHLevel(const HHLevel& _Origin);
    ~HHLevel();

    friend class HHTaskMgr;

    void Begin();  // 레벨이 시작되는 순간 or 레벨에 추가(합류) 하는 순간
    void Tick();
    void FinalTick();

    void AddObject(int LayerIdx, HHGameObject* _Object, bool bMoveChild = false);
    void RegisterAsParent(int LayerIdx, HHGameObject* _Object);
    void ClearObject();

    HHLayer* GetLayer(int _LayerIdx) { return m_Layer[_LayerIdx]; }
    LEVEL_STATE GetState() { return m_State; }

    HHGameObject* FindObjectByName(const wstring& _Name);

private:
    HHLayer*        m_Layer[MAX_LAYER];
    LEVEL_STATE     m_State;

    void ChangeState(LEVEL_STATE _NextState);

};
