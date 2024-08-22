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
    vector<HHGameObject*>   m_vecParentObj;     // �ش� ���̾� �Ҽ� ������Ʈ �߿��� �ֻ��� �θ� ������Ʈ�� ����
    vector<HHGameObject*>   m_vecObject;        // �ش� ���̾� �Ҽ� ������Ʈ �߿��� �θ� �ڽ� ������� ��� ������Ʈ
    const int               m_LayerIdx;         // ���̾� �ε���

};
