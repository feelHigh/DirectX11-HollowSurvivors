#pragma once
#include "HHAsset.h"

class HHShader :
    public HHAsset
{
public:
    HHShader(ASSET_TYPE _Type);
    ~HHShader();

    virtual int Load(const wstring& _FilePath) { return S_OK; }
    virtual int Save(const wstring& _FilePath) { return S_OK; }

protected:
    ComPtr<ID3DBlob> m_ErrBlob;

};
