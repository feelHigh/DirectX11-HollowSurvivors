#include "pch.h"
#include "HHEntity.h"

UINT HHEntity::g_ID = 0;

HHEntity::HHEntity()
	: m_ID(g_ID++)
{
}

HHEntity::HHEntity(const HHEntity& _Other)
	: m_ID(g_ID++)
	, m_Name(_Other.m_Name)
{
}

HHEntity::~HHEntity()
{
}
