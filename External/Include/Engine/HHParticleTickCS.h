#pragma once
#include "HHComputeShader.h"

class HHStructuredBuffer;

class HHParticleTickCS :
    public HHComputeShader
{
public:
    HHParticleTickCS();
    ~HHParticleTickCS();

    virtual int Binding() override;
    virtual void CalculateGroupNum() override;
    virtual void Clear() override;

    void SetParticleBuffer(HHStructuredBuffer* _Buffer) { m_ParticleBuffer = _Buffer; }
    void SetSpawnCount(HHStructuredBuffer* _Buffer) { m_SpawnCountBuffer = _Buffer; }
    void SetModuleBuffer(HHStructuredBuffer* _ModuleBuffer) { m_ModuleBuffer = _ModuleBuffer; }

    void SetParticleWorldPos(Vec3 _Pos) { m_ParticleWorldPos = _Pos; }
    void SetNoiseTexture(Ptr<HHTexture> _Noise) { m_NoiseTex = _Noise; }

private:
    HHStructuredBuffer* m_ParticleBuffer;
    HHStructuredBuffer* m_SpawnCountBuffer;
    HHStructuredBuffer* m_ModuleBuffer;

    Ptr<HHTexture>      m_NoiseTex;
    Vec3                m_ParticleWorldPos;

};
