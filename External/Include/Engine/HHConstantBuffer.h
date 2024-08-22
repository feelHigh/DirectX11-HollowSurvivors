#pragma once
#include "HHEntity.h"

class HHConstantBuffer :
    public HHEntity
{
public:
    CLONE_DISABLE(HHConstantBuffer);
    HHConstantBuffer();
    ~HHConstantBuffer();

    int Create(CONSTANT_BUFFER_TYPE _type, UINT _BufferSize);

    void SetData(void* _pData);
    void Binding();
    void Binding_CS();

private:
    ComPtr<ID3D11Buffer>    m_CB;
    D3D11_BUFFER_DESC       m_Desc;
    CONSTANT_BUFFER_TYPE    m_CBType;

};
