#include "pch.h"
#include "HHBlackboard.h"

HHBlackboard::HHBlackboard()
{
}

HHBlackboard::HHBlackboard(const HHBlackboard& _board)
	: HHEntity(_board)
	, m_mapBBData()
{
}

HHBlackboard::~HHBlackboard()
{
}

void HHBlackboard::AddBlackboardData(const wstring& _strKey, BB_DATA _Type, void* _Data)
{
	map<wstring, tBlackboardData>::iterator iter = m_mapBBData.find(_strKey);

	assert(iter == m_mapBBData.end());

	m_mapBBData.insert(make_pair(_strKey, tBlackboardData{ _Type , _Data }));
}

void* HHBlackboard::GetBlackboardData(const wstring& _strKey)
{
	map<wstring, tBlackboardData>::iterator iter = m_mapBBData.find(_strKey);

	if (iter == m_mapBBData.end())
		return nullptr;

	return iter->second.pData;
}
