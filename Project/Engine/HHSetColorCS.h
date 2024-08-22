#pragma once
#include "HHComputeShader.h"

class HHSetColorCS :
    public HHComputeShader
{
public:
    HHSetColorCS();
    ~HHSetColorCS();

    void SetTargetTexture(Ptr<HHTexture> _Tex) { m_TargetTex = _Tex; }
    void SetClearColor(Vec4 _Color) { m_ClearColor = _Color; }

private:
    Ptr<HHTexture>      m_TargetTex;
    Vec4                m_ClearColor;

    virtual int Binding() override;
    virtual void CalculateGroupNum() override;
    virtual void Clear() override;

};
