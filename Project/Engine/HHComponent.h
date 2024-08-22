#pragma once
#include "HHEntity.h"
#include "HHGameObject.h"

#define GET_OTHER_COMPONENT(Type) HH##Type* Type() { return m_Owner->Type(); }

class HHComponent :
    public HHEntity
{
public:
    CLONE_DISABLE(HHComponent);
    HHComponent(COMPONENT_TYPE _Type);
    HHComponent(const HHComponent& _Origin);
    ~HHComponent();

    friend class HHGameObject;

    virtual void Initialize() {}
    virtual void Begin();
    virtual void Tick();
    virtual void FinalTick() = 0;

    virtual void SaveToFile(FILE* _File) = 0;
    virtual void LoadFromFile(FILE* _File) = 0;

    COMPONENT_TYPE GetComponentType() { return m_Type; }
    HHGameObject* GetOwner() { return m_Owner; }

    GET_OTHER_COMPONENT(Transform);
    GET_OTHER_COMPONENT(MeshRender);
    GET_OTHER_COMPONENT(Camera);
    GET_OTHER_COMPONENT(Collider2D);
    GET_OTHER_COMPONENT(FlipbookRenderer);
    GET_OTHER_COMPONENT(Tilemap);
    GET_OTHER_COMPONENT(Light2D);
    GET_OTHER_COMPONENT(ParticleSystem);

private:
    const COMPONENT_TYPE    m_Type;
    HHGameObject*           m_Owner;

    void SetOwner(HHGameObject* _Object) { m_Owner = _Object; }

};
