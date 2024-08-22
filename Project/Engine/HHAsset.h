#pragma once
#include "HHEntity.h"

class HHAsset :
    public HHEntity
{
public:
    CLONE_DISABLE(HHAsset);
    HHAsset(ASSET_TYPE _Type);
    HHAsset(const HHAsset& _Other);
    ~HHAsset();

    template<typename T>
    friend class Ptr;

    friend class HHAssetMgr;

    const wstring& GetKey() { return m_Key; }
    const wstring& GetRelativePath() { return m_RelativePath; }
    ASSET_TYPE GetAssetType() { return m_Type; }
    UINT GetReferenceCount() { return m_RefCount; }
    bool IsEngineAsset() { return m_EngineAsset; }

private:
    wstring             m_Key;
    wstring             m_RelativePath;
    const ASSET_TYPE    m_Type;
    int                 m_RefCount;
    bool                m_EngineAsset;

    virtual int Load(const wstring& _FilePath) = 0;
    virtual int Save(const wstring& _RelativePath) = 0;

    void AddRef() { ++m_RefCount; }
    void Release()
    {
        --m_RefCount;
        if (m_RefCount <= 0)
        {
            delete this;
        }
    }

protected:
    void SetKey(const wstring& _Key) { m_Key = _Key; }
    void SetRelativePath(const wstring& _path) { m_RelativePath = _path; }
    void SetEngineAsset() { m_EngineAsset = true; }

};
