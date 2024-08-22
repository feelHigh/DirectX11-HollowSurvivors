#pragma once
#include "HHComponent.h"

class HHTransform :
    public HHComponent
{
public:
    CLONE(HHTransform);
    HHTransform();
    ~HHTransform();

    virtual void FinalTick() override;
    void Binding();

    void SetRelativePosition(Vec3 _Pos) { m_RelativePosition = _Pos; }
    void SetRelativeScale(Vec3 _Scale) { m_RelativeScale = _Scale; }
    void SetRelativeRotation(Vec3 _Rot) { m_RelativeRotation = _Rot; }

    void SetRelativePosition(float x, float y, float z) { m_RelativePosition = Vec3(x, y, z); }
    void SetRelativeScale(float x, float y, float z) { m_RelativeScale = Vec3(x, y, z); }
    void SetRelativeRotation(float x, float y, float z) { m_RelativeRotation = Vec3(x, y, z); }

    void SetWorldMatrix(const Matrix& matWorld) { m_matWorld = matWorld; }

    void SetIndependentScale(bool _Set) { m_IndependentScale = _Set; }
    bool IsIndependentScale() { return m_IndependentScale; }

    Vec3 GetRelativePosition() { return m_RelativePosition; }
    Vec3 GetWorldPosition() { return m_matWorld.Translation(); }
    Vec3 GetRelativeScale() { return m_RelativeScale; }
    Vec3 GetRelativeRoatation() { return m_RelativeRotation; }
    Vec3 GetRelativeDirection(DIRECTION_TYPE _Type) { return m_RelativeDirection[_Type]; }
    Vec3 GetWorldDirection(DIRECTION_TYPE _Type) { return m_WorldDirection[_Type]; }

    const Matrix& GetWorldMatrix() { return m_matWorld; }
    Vec3 GetWorldScale();

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

private:
    Vec3    m_RelativePosition;             // ����� ��ġ
    Vec3    m_RelativeScale;                // ����� ũ��
    Vec3    m_RelativeRotation;             // ����� ȸ��
    Vec3    m_RelativeDirection[3];         // ����� ����
    Vec3    m_WorldDirection[3];            // ���� ����

    Matrix  m_matWorld;                     // �̵�, ũ��, ȸ��
    bool    m_IndependentScale;             // �θ��� ũ�⿡ ���� �޴��� ����

};
