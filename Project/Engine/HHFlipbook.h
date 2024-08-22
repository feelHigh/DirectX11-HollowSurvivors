#pragma once
#include "HHAsset.h"

#include "HHSprite.h"

class HHFlipbook :
    public HHAsset
{
public:
    HHFlipbook();
    ~HHFlipbook();

    void FinalTick();

    void AddSprite(Ptr<HHSprite> _Sprite) { m_vecSprite.push_back(_Sprite); }
    Ptr<HHSprite> GetSprite(int _Idx) { return m_vecSprite[_Idx]; }
    int GetMaxFrameCount() { return (int)m_vecSprite.size(); }

    virtual int Load(const wstring& _FilePath) override;
    virtual int Save(const wstring& _FilePath) override;

private:
    vector<Ptr<HHSprite>>   m_vecSprite;

};
