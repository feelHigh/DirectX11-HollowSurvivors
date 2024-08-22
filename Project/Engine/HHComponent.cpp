#include "pch.h"
#include "HHComponent.h"

HHComponent::HHComponent(COMPONENT_TYPE _Type)
	: m_Type(_Type)
	, m_Owner(nullptr)
{
}

HHComponent::HHComponent(const HHComponent& _Origin)
	: m_Type(_Origin.m_Type)
	, m_Owner(nullptr)
{
}

HHComponent::~HHComponent()
{
}

void HHComponent::Begin()
{
}

void HHComponent::Tick()
{
}
