#include "pch.h"
#include "HHText.h"

#include "HHEngine.h"
#include "HHDevice.h"
#include "HHFontMgr.h"

#include "HHGameObject.h"
#include "HHTransform.h"

HHText::HHText()
	:HHComponent(COMPONENT_TYPE::GAME_TEXT)
	, m_TextInput{}
	, m_FontSize(32.f)
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

	HHFontMgr::GetInstance()->DrawFont(m_TextInput.c_str()
										, vPosition.x - (m_TextInput.length() * m_FontSize) / 4.5f
										, vPosition.y - m_FontSize / 2.f
										, m_FontSize, FONT_RGBA(255, 255, 225, 255));
}

void HHText::SaveToFile(FILE* _File)
{
	fwrite(&m_TextInput, sizeof(wstring), 1, _File);
	fwrite(&m_FontSize, sizeof(float), 1, _File);
}

void HHText::LoadFromFile(FILE* _File)
{
	fread(&m_TextInput, sizeof(wstring), 1, _File);
	fread(&m_FontSize, sizeof(float), 1, _File);
}
