#pragma once
#include "HHAsset.h"

class HHSound :
    public HHAsset
{
public:
    HHSound();
    ~HHSound();

    virtual int Load(const wstring& _FilePath) override;
    virtual int Save(const wstring& _FilePath) override;

    // _iRoopCount : 0 (무한반복),  _fVolume : 0 ~ 1(Volume), _bOverlap : 소리 중첩 가능여부
    int Play(int _iRoopCount, float _fVolume, bool _bOverlap);
    void Stop();
    void RemoveChannel(FMOD::Channel* _pTargetChannel);

    // 0 ~ 1
    void SetVolume(float _f, int _iChannelIdx);

private:
    FMOD::Sound*            m_Sound;        // Sound 버퍼
    list<FMOD::Channel*>	m_listChannel;  // Sound 가 재생되고 있는 채널 리스트

};
