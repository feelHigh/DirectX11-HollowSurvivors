#pragma once
#include "HHAsset.h"
#include "HHGameObject.h"

#include "HHEngine.h"

class HHPrefab :
    public HHAsset
{
public:
    HHPrefab();
    ~HHPrefab();

    friend class HHEngine;

    HHGameObject* Instantiate();

    void SetProtoObject(HHGameObject* _Object) { m_ProtoObject = _Object; }

    virtual int Load(const wstring& _FilePath) override;
    virtual int Save(const wstring& _FilePath) override;

private:
    class HHGameObject* m_ProtoObject;

    static OBJECT_SAVE  g_ObjectSaveFunc;
    static OBJECT_LOAD  g_ObjectLoadFunc;

};
