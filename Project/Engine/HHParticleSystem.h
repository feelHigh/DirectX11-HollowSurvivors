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
    virtual void SaveToFile(FILE* _File) override;   // ���Ͽ� ������Ʈ�� ������ ����
    virtual void LoadFromFile(FILE* _File) override; // ���Ͽ� ������Ʈ�� ������ �ε�

    void SetParticleTexture(Ptr<HHTexture> _Texture) { m_ParticleTex = _Texture; }

    void CalculateSpawnCount();

private:
    Ptr<HHParticleTickCS>   m_TickCS;
    HHStructuredBuffer*     m_ParticleBuffer;       // ��� ��ƼŬ ����
    HHStructuredBuffer*     m_SpawnCountBuffer;     // ��ƼŬ Ȱ��ȭ ���� ���޿� ����
    HHStructuredBuffer*     m_ModuleBuffer;         // Module Data Buffer

    Ptr<HHTexture>          m_ParticleTex;
    float                   m_Time;                 // �����ð�
    float                   m_BurstTime;            // SpawnBurst üũ�� ����

    int                     m_MaxParticleCount;     // ��ƼŬ �ִ� ����

    tParticleModule         m_Module;               // ��ƼŬ�� ��� ����
};
