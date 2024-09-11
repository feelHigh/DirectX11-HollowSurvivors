#pragma once
#include "HHEntity.h"

enum class BB_DATA
{
    INT,
    FLOAT,
    VEC2,
    VEC3,
    VEC4,
    OBJECT,
};

struct tBlackboardData
{
    BB_DATA     Type;
    void*       pData;
};

class HHBlackboard :
    public HHEntity
{
    CLONE(HHBlackboard);
public:
    HHBlackboard();
    HHBlackboard(const HHBlackboard& _board);
    ~HHBlackboard();

    void AddBlackboardData(const wstring& _strKey, BB_DATA _Type, void* _Data);
    void* GetBlackboardData(const wstring& _strKey);

private:
    map<wstring, tBlackboardData>   m_mapBBData;

};
