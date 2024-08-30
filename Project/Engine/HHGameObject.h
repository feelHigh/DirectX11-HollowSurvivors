#pragma once
#include "HHEntity.h"

class HHComponent;
class HHRenderComponent;
class HHScript;

#define GET_COMPONENT(Type, TYPE) class HH##Type* Type() { return (HH##Type*)GetComponent(COMPONENT_TYPE::TYPE); }

class HHGameObject :
    public HHEntity
{
public:
    CLONE(HHGameObject);
    HHGameObject();
    HHGameObject(const HHGameObject& _Origin);
    ~HHGameObject();

    friend class HHLevel;
    friend class HHLayer;
    friend class HHTaskMgr;

    void Begin();
    void Tick();
    virtual void FinalTick();
    void Render();

    void                AddComponent(HHComponent* _Component);
    HHComponent*        GetComponent(COMPONENT_TYPE _Type) { return m_arrCom[(UINT)_Type]; }

    template<typename T>
    T* GetUnComponent(COMPONENT_TYPE _Type)
    {
        T* tComp = dynamic_cast<T*>(m_arrCom[(UINT)_Type]);
        if (tComp != nullptr)
            return tComp;

        return tComp;
    }

    HHRenderComponent*  GetRenderComponent()    { return m_RenderCom; }
    HHGameObject*       GetParentObject()       { return m_ParentObj; }
    int                 GetLayerIndex()         { return m_LayerIdx; }

    void AddChild(HHGameObject* _ChildObject);
    const vector<HHGameObject*>& GetChildObjects() { return m_vecChildObj; }
    const vector<HHScript*> GetScripts() { return m_vecScript; }

    bool IsAncestor(HHGameObject* _Object);
    bool IsDeadObject() { return m_Dead; }

    void DisconnectWithLayer();

    // Unregister : 등록을 취소하다, 등록하는 행위를 취소하다
    // Deregister : 등록된것을 취소하다
    void DeregisterChild();

    GET_COMPONENT(Transform, TRANSFORM);
    GET_COMPONENT(MeshRender, MESHRENDER);
    GET_COMPONENT(Camera, CAMERA);
    GET_COMPONENT(Collider2D, COLLIDER2D);
    GET_COMPONENT(FlipbookRenderer, FLIPBOOK_RENDERER);
    GET_COMPONENT(Tilemap, TILEMAP);
    GET_COMPONENT(Light2D, LIGHT2D);
    GET_COMPONENT(ParticleSystem, PARTICLESYSTEM);
    GET_COMPONENT(TextRenderer, TEXTRENDERER);
    GET_COMPONENT(Text, GAME_TEXT);
    GET_COMPONENT(Button, GAME_BUTTON);

private:
    HHComponent*            m_arrCom[(UINT)COMPONENT_TYPE::END];
    HHRenderComponent*      m_RenderCom;
    vector<HHScript*>       m_vecScript;

    HHGameObject*           m_ParentObj;
    vector<HHGameObject*>   m_vecChildObj;

    int                     m_LayerIdx;

    bool                    m_Dead;

};
