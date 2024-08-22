#pragma once
#include "HHComponent.h"

class HHCollider2D :
    public HHComponent
{
public:
    CLONE(HHCollider2D);
    HHCollider2D();
    HHCollider2D(const HHCollider2D& _Origin);
    ~HHCollider2D();

    virtual void FinalTick() override;

    virtual void BeginOverlap(HHCollider2D* _Other);
    virtual void Overlap(HHCollider2D* _Other);
    virtual void EndOverlap(HHCollider2D* _Other);

    void SetOffset(Vec3 _Offset) { m_Offset = _Offset; }
    void SetScale(Vec3 _Scale) { m_Scale = _Scale; }
    void SetIndependentScale(bool _Set) { m_IndependentScale = _Set; }

    Vec3 GetOffset() { return m_Offset; }
    Vec3 GetScale() { return m_Scale; }
    Vec3 GetWorldPosition() { return m_matColWorld.Translation(); }
    Matrix GetWorldMatrix() { return m_matColWorld; }

    Vec3 GetFinalPos() { return m_FinalPos; }
    int GetOverlapCount() { return m_OverlapCount; }

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

private:
    Vec3    m_Offset;
    Vec3    m_Scale;            // 배율 or 절대 크기
    Vec3    m_FinalPos;
    Matrix  m_matColWorld;      // 충돌체의 최종 월드 형태
    int     m_OverlapCount;
    bool    m_IndependentScale; // 오브젝트의 크기에 영향 받을지 여부

};