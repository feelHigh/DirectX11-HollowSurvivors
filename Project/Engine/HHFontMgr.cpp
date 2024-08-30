#include "pch.h"
#include "HHFontMgr.h"

#include "HHDevice.h"

HHFontMgr::HHFontMgr()
	: m_FW1Factory(nullptr)
	, m_FontWrapper(nullptr)
{
}

HHFontMgr::~HHFontMgr()
{
	if (nullptr != m_FW1Factory)
		m_FW1Factory->Release();

	if (nullptr != m_FontWrapper)
		m_FontWrapper->Release();
}

void HHFontMgr::Initialize()
{
	if (FAILED(FW1CreateFactory(FW1_VERSION, &m_FW1Factory)))
	{
		assert(nullptr);
	}

	if (FAILED(m_FW1Factory->CreateFontWrapper(DEVICE, L"ThaleahFat", &m_FontWrapper)))
	{
		assert(nullptr);
	}
}

void HHFontMgr::Tick()
{
}

void HHFontMgr::DrawFont(const wchar_t* _pStr, float _fPosX, float _fPosY, float _fFontSize, UINT _Color)
{
	m_FontWrapper->DrawString(
		CONTEXT,
		_pStr,				// String
		_fFontSize,			// Font size
		_fPosX,				// X position
		_fPosY,				// Y position
		_Color,				// Text color, 0xAaBbGgRr
		FW1_RESTORESTATE    // Flags (for example FW1_RESTORESTATE to keep context states unchanged)
	);
}
