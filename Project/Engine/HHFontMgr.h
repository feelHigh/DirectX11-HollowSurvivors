#pragma once

#include <FontEngine/FW1FontWrapper.h>
#include <FontEngine/FW1CompileSettings.h>

#ifdef _DEBUG
#pragma comment(lib, "FontEngine/FW1FontWrapper_debug.lib")
#else
#pragma comment(lib, "FontEngine/FW1FontWrapper.lib"))
#endif

#define FONT_RGBA(r, g, b, a) (((((BYTE)a << 24 ) | (BYTE)b << 16) | (BYTE)g << 8) | (BYTE)r)

class HHFontMgr :
    public HHSingleton<HHFontMgr>
{
    SINGLE(HHFontMgr);

public:
    void Initialize();
    void Tick();

    void DrawFont(const wchar_t* _pStr, float _fPosX, float _fPosY, float _fFontSize, UINT _Color);
    void DrawFont(wstring _str, UINT32 _color, wstring _font, DWRITE_FONT_WEIGHT _fontweight, float _x, float _y, float _fontsize = 32.0f);

private:
    IFW1Factory*        m_FW1Factory;
    IDWriteFactory*     m_WriteFactory;
    IFW1FontWrapper*    m_FontWrapper;

};
