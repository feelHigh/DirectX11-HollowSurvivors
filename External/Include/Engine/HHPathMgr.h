#pragma once

class HHPathMgr
	: public HHSingleton<HHPathMgr>
{
	SINGLE(HHPathMgr);

public:
	void Initialize();

	const wstring& GetContentPath() { return m_Content; }
	const wstring& GetSolutionPath() { return m_Solution; }
	wstring GetRelativePath(const wstring& _FilePath);

	const wstring& GetImGuiResourcePath() { return m_ImGuiResource; }

private:
	wstring		m_Content;
	wstring		m_Solution;
	wstring		m_ImGuiResource;

	void GetParentPath(_Inout_ wchar_t* _Buffer);

};
