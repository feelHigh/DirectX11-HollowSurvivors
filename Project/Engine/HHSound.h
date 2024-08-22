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

    // _iRoopCount : 0 (���ѹݺ�),  _fVolume : 0 ~ 1(Volume), _bOverlap : �Ҹ� ��ø ���ɿ���
    int Play(int _iRoopCount, float _fVolume, bool _bOverlap);
    void Stop();
    void RemoveChannel(FMOD::Channel* _pTargetChannel);

    // 0 ~ 1
    void SetVolume(float _f, int _iChannelIdx);

private:
    FMOD::Sound*            m_Sound;        // Sound ����
    list<FMOD::Channel*>	m_listChannel;  // Sound �� ����ǰ� �ִ� ä�� ����Ʈ

};
