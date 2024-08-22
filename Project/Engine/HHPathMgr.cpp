#include "pch.h"
#include "HHPathMgr.h"
#include "HHEngine.h"

HHPathMgr::HHPathMgr()
{
}

HHPathMgr::~HHPathMgr()
{
}

void HHPathMgr::Initialize()
{
	// 실행경로를 얻어낸다
	wchar_t szBuffer[256] = {};
	GetCurrentDirectory(256, szBuffer);

	// bin 폴더의 상위폴더로 접근한다.
	GetParentPath(szBuffer);

	// \\Content\\ 를 붙여둔다
	m_Content = szBuffer;
	m_Content += L"\\content\\";

	GetCurrentDirectory(256, szBuffer);

	// bin 폴더의 상위폴더로 접근한다.
	GetParentPath(szBuffer);

	// \\imgui_resource\\ 를 붙여둔다
	m_ImGuiResource = szBuffer;
	m_ImGuiResource += L"\\imgui_resource\\";
}

wstring HHPathMgr::GetRelativePath(const wstring& _FilePath)
{
	size_t FindPos = _FilePath.find(m_Content);
	if (FindPos == wstring::npos)
		return L"";

	return _FilePath.substr(FindPos + m_Content.length(), _FilePath.length());
}

void HHPathMgr::GetParentPath(_Inout_ wchar_t* _Buffer)
{
	size_t len = wcslen(_Buffer);

	for (size_t i = len - 1; 0 < i; --i)
	{
		if (L'\\' == _Buffer[i])
		{
			_Buffer[i] = L'\0';
			break;
		}
	}
}
