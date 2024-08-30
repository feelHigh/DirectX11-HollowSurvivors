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

	void SetText(wstring _Text) { m_TextInput = _Text; }
	void SetFontSize(float _size) { m_FontSize = _size; }

	const wstring& GetText() const { return  m_TextInput; }
	float GetFontSize() { return m_FontSize; }

private:
	wstring		m_TextInput;
	float		m_FontSize;

};
