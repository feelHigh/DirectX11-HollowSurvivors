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
    vector<Ptr<HHFlipbook>>         m_vecFlipbook;  // FlipBook ���
    Ptr<HHFlipbook>                 m_CurFlipbook;  // ���� ������� FlipBook
    Ptr<HHSprite>                   m_CurFrmSprite; // ���� ������� FlipBook ���� ���� ������ �ε����� �ش��ϴ� ��������Ʈ
    int                             m_CurFrmIdx;    // ���� ������� FlipBook ���� ���° Sprite �� ��������� �ε��� ���
    float                           m_FPS;          // ���� ������� FlipBook �� �ʴ� ������ ���� ��
    float                           m_AccTime;      // ���� �ð��� üũ
    bool                            m_Repeat;
    bool                            m_Finish;       // FlipBook ����� ���� �����ߴ��� ����

};
