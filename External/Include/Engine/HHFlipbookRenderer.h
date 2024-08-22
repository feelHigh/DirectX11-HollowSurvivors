#pragma once
#include "HHComponent.h"

class HHFlipbook;

class HHFlipbookRenderer :
    public HHComponent
{
public:
    CLONE(HHFlipbookRenderer);
    HHFlipbookRenderer();
    HHFlipbookRenderer(HHFlipbookRenderer& _Origin);
    ~HHFlipbookRenderer();

    virtual void FinalTick() override;

    void AddFlipbook(int _Idx, Ptr<HHFlipbook> _Flipbook);
    Ptr<HHFlipbook> FindFlipbook(const wstring& _Key);

    Ptr<HHSprite> GetCurrentSprite() { return m_CurFrmSprite; }

public:
    void Play(int _FlipbookIndex, float _FPS, bool _Repeat);
    void Reset();
    void Binding();
    static void Clear();

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

private:
    vector<Ptr<HHFlipbook>>         m_vecFlipbook;  // FlipBook 목록
    Ptr<HHFlipbook>                 m_CurFlipbook;  // 현재 재생중인 FlipBook
    Ptr<HHSprite>                   m_CurFrmSprite; // 현재 재생중인 FlipBook 에서 현재 프레임 인덱스에 해당하는 스프라이트
    int                             m_CurFrmIdx;    // 현재 재생중인 FlipBook 에서 몇번째 Sprite 가 재생중인지 인덱스 기록
    float                           m_FPS;          // 현재 재생중인 FlipBook 의 초당 프레임 진행 수
    float                           m_AccTime;      // 누적 시간값 체크
    bool                            m_Repeat;
    bool                            m_Finish;       // FlipBook 재생이 끝에 도달했는지 여부

};
