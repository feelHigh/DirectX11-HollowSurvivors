#pragma once
#include "HHComponent.h"

#include "HHFontMgr.h"

class HHText :
	public HHComponent
{
public:
	CLONE(HHText);
	HHText();
	virtual ~HHText();

	virtual void Tick();
	virtual void Render();

	virtual void FinalTick() {};

	virtual void SaveToFile(FILE* _File) override;
	virtual void LoadFromFile(FILE* _File) override;

	void SetFont(wstring _font) { m_Font = _font; }
	void SetFontSize(float _size) { m_FontSize = _size; }
	void SetColor(Vec4 _color) { m_Color = _color; }
	void SetFontWeight(DWRITE_FONT_WEIGHT _weight) { m_Weight = _weight; }
	void SetText(wstring _str) { m_TextInput = _str; }

	wstring GetFont() { return m_Font; }
	float GetFontSize() { return m_FontSize; }
	Vec4 GetColor() { return m_Color; }
	DWRITE_FONT_WEIGHT GetFontWeight() { return m_Weight; }
	wstring GetText() { return  m_TextInput; }

private:
	wstring				m_Font;
	float				m_FontSize;
	Vec4				m_Color;
	DWRITE_FONT_WEIGHT	m_Weight;
	wstring				m_TextInput;

};
