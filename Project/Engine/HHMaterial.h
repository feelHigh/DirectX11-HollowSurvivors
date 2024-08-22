#pragma once
#include "HHAsset.h"
#include "HHTexture.h"
#include "HHGraphicShader.h"
#include "Ptr.h"

class HHMaterial :
    public HHAsset
{
public:
    CLONE(HHMaterial);
    HHMaterial(bool _IsEngineAsset = false);
    ~HHMaterial();

    virtual int Save(const wstring& _RelativePath) override;
    virtual int Load(const wstring& _FilePath) override;
    void Binding();

    template<typename T>
    void SetScalarParam(SCALAR_PARAM _Param, const T& _Data);
    void* GetScalarParam(SCALAR_PARAM _Param);

    void SetTextureParam(TEXTURE_PARAM _Param, Ptr<HHTexture> _Tex) { m_arrTex[_Param] = _Tex; }
    Ptr<HHTexture> GetTextureParam(TEXTURE_PARAM _Param) { return m_arrTex[(UINT)_Param]; }

    void SetShader(Ptr<HHGraphicShader> _Shader) { m_Shader = _Shader; }
    Ptr<HHGraphicShader> GetShader() { return m_Shader; }

private:
    Ptr<HHGraphicShader>        m_Shader;
    tMaterialConstant           m_MaterialConst;
    Ptr<HHTexture>              m_arrTex[TEXTURE_PARAM::END];

};

template<typename T>
void HHMaterial::SetScalarParam(SCALAR_PARAM _Param, const T& _Data)
{
    if constexpr (std::is_same_v<T, int>) { m_MaterialConst.iArr[_Param] = _Data; }
    if constexpr (std::is_same_v<T, float>) { m_MaterialConst.fArr[_Param - FLOAT_0] = _Data; }
    if constexpr (std::is_same_v<T, Vec2>) { m_MaterialConst.v2Arr[_Param - VEC2_0] = _Data; }
    if constexpr (std::is_same_v<T, Vec4>) { m_MaterialConst.v4Arr[_Param - VEC4_0] = _Data; }
    if constexpr (std::is_same_v<T, Matrix>) { m_MaterialConst.matArr[_Param - MAT_0] = _Data; }
}
