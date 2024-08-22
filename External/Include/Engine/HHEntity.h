#pragma once

class HHEntity
{
public:
	CLONE_DISABLE(HHEntity);
	HHEntity();
	HHEntity(const HHEntity& _Other);
	virtual ~HHEntity();

	void SetName(const wstring& _Name) { m_Name = _Name; }
	const wstring& GetName() { return m_Name; }
	UINT GetID() { return m_ID; }

private:
	wstring		m_Name;
	const UINT	m_ID;
	static UINT g_ID;

};
