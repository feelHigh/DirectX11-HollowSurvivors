#pragma once

#include <vector>
#include <string>

enum SCRIPT_TYPE
{
	BUTTONSCRIPT,
	CAMERAMOVESCRIPT,
	LEVELBACKGROUNDSCRIPT,
	MOUSECURSORSCRIPT,
	PLAYERSCRIPT,
	SMALLGIRLSCRIPT,
	TILEMAPSCRIPT,
	TITLELOGOSCRIPT,
};

using namespace std;

class HHScript;

class HHScriptMgr
{
public:
	static void GetScriptInfo(vector<wstring>& _vec);
	static HHScript * GetScript(const wstring& _strScriptName);
	static HHScript * GetScript(UINT _iScriptType);
	static const wchar_t * GetScriptName(HHScript * _pScript);
};
