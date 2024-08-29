#include "pch.h"
#include "HHText.h"

#include "HHEngine.h"
#include "HHDevice.h"
#include "HHFontMgr.h"

#include "HHGameObject.h"
#include "HHTransform.h"

HHText::HHText()
	:HHComponent(COMPONENT_TYPE::GAME_TEXT)
	, m_Font(L"Arial")
	, m_FontSize(32.f)
	, m_Color(0xffffffff)
	, m_Weight(DWRITE_FONT_WEIGHT_NORMAL)
{
}

HHText::~HHText()
{
}

void HHText::Tick()
{
}

void HHText::Render()
{
	Vec3 vPosition = GetOwner()->GetUnComponent<HHTransform>(COMPONENT_TYPE::TRANSFORM)->GetRelativePosition();

	vPosition.x *= -1.f;
	vPosition.y *= -1.f;

	vPosition.x += HHDevice::GetInstance()->GetResolution().x / 2.f;
	vPosition.y += HHDevice::GetInstance()->GetResolution().y / 2.f;

	UINT32 uColor = 0;
	uColor |= (UINT)m_Color.w;
	uColor = uColor << 8;
	uColor |= (UINT)m_Color.z;
	uColor = uColor << 8;
	uColor |= (UINT)m_Color.y;
	uColor = uColor << 8;
	uColor |= (UINT)m_Color.x;

	HHFontMgr::GetInstance()->DrawFont(m_TextInput, uColor, m_Font, DWRITE_FONT_WEIGHT_DEMI_BOLD
										, vPosition.x - (m_TextInput.size() * m_FontSize) / 2.f
										, vPosition.y - m_FontSize / 2.f, m_FontSize);
}

void HHText::SaveToFile(FILE* _File)
{
}

void HHText::LoadFromFile(FILE* _File)
{
}
