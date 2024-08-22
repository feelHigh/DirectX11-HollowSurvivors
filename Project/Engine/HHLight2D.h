#pragma once
#include "HHComponent.h"

class HHLight2D :
    public HHComponent
{
public:
    CLONE(HHLight2D);
    HHLight2D();
    ~HHLight2D();

    virtual void FinalTick() override;

    void SetLightType(LIGHT_TYPE _Type);
    void SetRadius(float _Radius) { m_Info.Radius = _Radius; }
    void SetAngle(float _Angle) { m_Info.Angle = _Angle; }
    void SetLightColor(Vec3 _Color) { m_Info.LightEssence.Color = _Color; }
    void SetLightAmbient(Vec3 _Amb) { m_Info.LightEssence.Ambient = _Amb; }

    LIGHT_TYPE GetLightType() { return m_Info.Type; }
    float GetRadius() { return m_Info.Radius; }
    float GetAngle() { return m_Info.Angle; }
    Vec3 GetLightColor() { return m_Info.LightEssence.Color; }
    Vec3 GetLightAmbient() { return m_Info.LightEssence.Ambient; }

    const tLightInfo& GetLightInfo() { return m_Info; }

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

private:
    tLightInfo      m_Info;

};
