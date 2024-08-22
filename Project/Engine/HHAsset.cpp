#include "pch.h"
#include "HHAsset.h"

HHAsset::HHAsset(ASSET_TYPE _Type)
	: m_Type(_Type)
	, m_RefCount(0)
{
}

HHAsset::HHAsset(const HHAsset& _Other)
	: HHEntity(_Other)
	, m_Key(_Other.m_Key)
	, m_RelativePath(_Other.m_RelativePath)
	, m_Type(_Other.m_Type)
	, m_RefCount(0)
{
}

HHAsset::~HHAsset()
{
}
