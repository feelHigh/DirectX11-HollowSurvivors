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

	if (FAILED(m_FW1Factory->CreateFontWrapper(DEVICE, L"Arial", &m_FontWrapper)))
	{
		assert(nullptr);
	}
}

void HHFontMgr::Tick()
{
	e_Font = L"ThaleahFat";
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

void HHFontMgr::DrawFont(wstring _str, UINT32 _color, wstring _font, DWRITE_FONT_WEIGHT _fontweight, float _x, float _y, float _fontsize)
{
	IDWriteTextFormat* pWriteTextFormat;
	HRESULT _result = m_WriteFactory->CreateTextFormat(_font.c_str(),
														NULL,
														_fontweight,
														DWRITE_FONT_STYLE_NORMAL,
														DWRITE_FONT_STRETCH_NORMAL,
														_fontsize,
														L"",
														&pWriteTextFormat);

	IDWriteTextLayout* pTextLayout = nullptr;
	HRESULT hResult = m_WriteFactory->CreateTextLayout(_str.c_str(),
														static_cast<UINT32>(_str.size()),
														pWriteTextFormat,
														0.f,
														0.0f,
														&pTextLayout);

	pTextLayout->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);

	m_FontWrapper->DrawTextLayout(CONTEXT, pTextLayout, _x, _y, _color, 0);
}
