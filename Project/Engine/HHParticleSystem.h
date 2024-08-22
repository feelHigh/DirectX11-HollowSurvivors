#pragma once
#include "HHRenderComponent.h"

#include "HHParticleTickCS.h"

class HHStructuredBuffer;

struct tSpawnCount
{
    UINT    SpawnCount;
    UINT    padding[3];
};

class HHParticleSystem :
    public HHRenderComponent
{
public:
    CLONE(HHParticleSystem);
    HHParticleSystem();
    HHParticleSystem(const HHParticleSystem& _Other);
    ~HHParticleSystem();

    virtual void FinalTick() override;
    virtual void Render() override;
    virtual void SaveToFile(FILE* _File) override;   // 파일에 컴포넌트의 정보를 저장
    virtual void LoadFromFile(FILE* _File) override; // 파일에 컴포넌트의 정보를 로드

    void SetParticleTexture(Ptr<HHTexture> _Texture) { m_ParticleTex = _Texture; }

    void CalculateSpawnCount();

private:
    Ptr<HHParticleTickCS>   m_TickCS;
    HHStructuredBuffer*     m_ParticleBuffer;       // 모든 파티클 정보
    HHStructuredBuffer*     m_SpawnCountBuffer;     // 파티클 활성화 숫자 전달용 버퍼
    HHStructuredBuffer*     m_ModuleBuffer;         // Module Data Buffer

    Ptr<HHTexture>          m_ParticleTex;
    float                   m_Time;                 // 누적시간
    float                   m_BurstTime;            // SpawnBurst 체크용 변수

    int                     m_MaxParticleCount;     // 파티클 최대 개수

    tParticleModule         m_Module;               // 파티클의 기능 정의
};
