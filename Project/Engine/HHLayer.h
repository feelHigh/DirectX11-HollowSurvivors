#pragma once
#include "HHEntity.h"

class HHGameObject;

class HHLayer :
    public HHEntity
{
public:
    CLONE(HHLayer);
    HHLayer(int _LayerIdx);
    HHLayer(const HHLayer& _Origin);
    ~HHLayer();

    void Begin();
    void Tick();
    void FinalTick();

    int GetLayerIdx() { return m_LayerIdx; }
    void AddObject(HHGameObject* _Object, bool _bMoveChild);
    const vector<HHGameObject*>& GetParentObjects() { return m_vecParentObj; }
    const vector<HHGameObject*>& GetObjects() { return m_vecObject; }

    void ClearObject() { m_vecObject.clear(); }
    void RegisterGameObject(HHGameObject* _Object) { m_vecObject.push_back(_Object); }
    void DisconnectWithObject(HHGameObject* _Object);

    void RegisterAsParentLayer(HHGameObject* _Object);
    void DeregisterObjectAsParent(HHGameObject* _Object);
    void DeregisterObject(HHGameObject* _Object);

private:
    vector<HHGameObject*>   m_vecParentObj;     // 해당 레이어 소속 오브젝트 중에서 최상위 부모 오브젝트만 관리
    vector<HHGameObject*>   m_vecObject;        // 해당 레이어 소속 오브젝트 중에서 부모 자식 상관없는 모든 오브젝트
    const int               m_LayerIdx;         // 레이어 인덱스

};
