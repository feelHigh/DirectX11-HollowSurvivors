#pragma once
#include "HHComponent.h"

#include "HHTimeMgr.h"
#include "HHKeyMgr.h"
#include "HHAssetMgr.h"
#include "components.h"

enum class SCRIPT_PARAM
{
    INT,
    FLOAT,
    VEC2,
    VEC3,
    VEC4,
    TEXTURE,
    PREFAB,
};

struct tScriptParam
{
    SCRIPT_PARAM    Type;
    void*           pData;
    string          Desc;
    DWORD_PTR       Param_0;
    DWORD_PTR       Param_1;
};

class HHScript :
    public HHComponent
{
public:
    HHScript(UINT _Type);
    ~HHScript();

    virtual void Begin() override {}
    virtual void Tick() = 0;
    virtual void FinalTick() final override {}

    HHRenderComponent* GetRenderComponent() { return GetOwner()->GetRenderComponent(); }
    UINT GetScriptType() { return m_ScriptType; }
    const vector<tScriptParam>& GetScriptParam() { return m_ScriptParam; }

    virtual void BeginOverlap(HHCollider2D* _OwnCollider, HHGameObject* _OtherObject, HHCollider2D* _OtherCollider) {}
    virtual void Overlap(HHCollider2D* _OwnCollider, HHGameObject* _OtherObject, HHCollider2D* _OtherCollider) {}
    virtual void EndOverlap(HHCollider2D* _OwnCollider, HHGameObject* _OtherObject, HHCollider2D* _OtherCollider) {}

    virtual void SaveToFile(FILE* _File) = 0;
    virtual void LoadFromFile(FILE* _File) = 0;

private:
    UINT                    m_ScriptType;
    vector<tScriptParam>    m_ScriptParam;

protected:
    void AddScriptParam(SCRIPT_PARAM _Type, const string& _Desc, void* _pData, DWORD_PTR _Param0 = 0, DWORD_PTR _Param1 = 0)
    {
        m_ScriptParam.push_back(tScriptParam{ _Type,_pData, _Desc, _Param0, _Param1 });
    }

    void Instantiate(Ptr<HHPrefab> _Pref, int _LayerIdx, Vec3 _WorldPos, const wstring& _Name = L"");

};
