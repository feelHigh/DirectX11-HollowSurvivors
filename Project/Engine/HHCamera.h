#pragma once
#include "HHComponent.h"

class HHGameObject;

enum PROJECTION_TYPE
{
    ORTHOGRAPHIC,   // ����
    PERSPECTIVE,    // ����
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
    void SetLayerAll() { m_LayerCheck = 0xffffffff; }   // ��� ���̾� ǥ��
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
    int                     m_Priority;         // �켱 ����
    UINT                    m_LayerCheck;       // ���ϴ� ���̾ ī�޶� ǥ��

    PROJECTION_TYPE         m_ProjectionType;   // ���� ����

    float                   m_Width;            // �ʺ�
    float                   m_Height;           // ����
    float                   m_AspectRatio;      // ��Ⱦ��
    float                   m_Far;              // ī�޶� �� �� �ִ� �þ� �Ÿ�
    float                   m_FOV;              // Field Of View(�þ� ����, �þ� ��)
    float                   m_ProjectionScale;

    Matrix                  m_matView;          // �� ���
    Matrix                  m_matProjection;    // ���� ���

    // Domain �ϰ� ó��
    vector<HHGameObject*>   m_DomainSort[(UINT)SHADER_DOMAIN::DOMAIN_NONE];

    void SortGameObject();
};
