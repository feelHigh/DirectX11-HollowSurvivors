#pragma once
#include "HHComponent.h"

class HHGameObject;

enum PROJECTION_TYPE
{
    ORTHOGRAPHIC,   // 직교
    PERSPECTIVE,    // 원근
};

class HHCamera :
    public HHComponent
{
public:
    CLONE(HHCamera);
    HHCamera();
    ~HHCamera();

    virtual void Begin() override;
    virtual void FinalTick() override;
    void Render();

    void Render(vector<HHGameObject*>& _vecObj);
    void PostProcessRender(vector<HHGameObject*>& _vecObj);

    void SetPriority(int _Priority) { m_Priority = _Priority; }
    void SetLayer(UINT _LayerIdx, bool _bCheck)
    {
        if (_bCheck)
            m_LayerCheck |= (1 << _LayerIdx);
        else
            m_LayerCheck &= ~(1 << _LayerIdx);
    }
    void SetLayerAll() { m_LayerCheck = 0xffffffff; }   // 모든 레이어 표시
    bool GetLayerCheck(UINT _LayerIdx) { return m_LayerCheck & (1 << _LayerIdx); }

    void SetProjectionType(PROJECTION_TYPE _Type) { m_ProjectionType = _Type; }
    PROJECTION_TYPE GetProjectionType() { return m_ProjectionType; }

    void SetWidth(float _Width)
    {
        m_Width = _Width;
        m_AspectRatio = m_Width / m_Height;
    }

    void SetHeight(float _Height)
    {
        m_Height = _Height;
        m_AspectRatio = m_Width / m_Height;
    }

    float GetWidth() { return m_Width; }
    float GetHeight() { return m_Height; }
    float GetAspectRatio() { return m_AspectRatio; }

    void SetFar(float _Far) { m_Far = _Far; }
    float GetFar() { return m_Far; }

    void SetFOV(float _FOV) { m_FOV = _FOV; }
    float GetFOV() { return m_FOV; }

    void SetScale(float _Scale) { m_ProjectionScale = _Scale; }
    float GetScale() { return m_ProjectionScale; }

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

private:
    int                     m_Priority;         // 우선 순위
    UINT                    m_LayerCheck;       // 원하는 레이어만 카메라에 표시

    PROJECTION_TYPE         m_ProjectionType;   // 투영 종류

    float                   m_Width;            // 너비
    float                   m_Height;           // 높이
    float                   m_AspectRatio;      // 종횡비
    float                   m_Far;              // 카메라가 볼 수 있는 시야 거리
    float                   m_FOV;              // Field Of View(시야 범위, 시야 각)
    float                   m_ProjectionScale;

    Matrix                  m_matView;          // 뷰 행렬
    Matrix                  m_matProjection;    // 투영 행렬

    // Domain 일괄 처리
    vector<HHGameObject*>   m_DomainSort[(UINT)SHADER_DOMAIN::DOMAIN_NONE];

    void SortGameObject();
};
