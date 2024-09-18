#include "pch.h"
#include "HHScriptMgr.h"

#include "HHButtonScript.h"
#include "HHCameraMoveScript.h"
#include "HHLevelBackgroundScript.h"
#include "HHMouseCursorScript.h"
#include "HHPlayerScript.h"
#include "HHSmallGirlScript.h"
#include "HHTilemapScript.h"
#include "HHTitleLogoScript.h"

void HHScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"HHButtonScript");
	_vec.push_back(L"HHCameraMoveScript");
	_vec.push_back(L"HHLevelBackgroundScript");
	_vec.push_back(L"HHMouseCursorScript");
	_vec.push_back(L"HHPlayerScript");
	_vec.push_back(L"HHSmallGirlScript");
	_vec.push_back(L"HHTilemapScript");
	_vec.push_back(L"HHTitleLogoScript");
}

HHScript * HHScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"HHButtonScript" == _strScriptName)
		return new HHButtonScript;
	if (L"HHCameraMoveScript" == _strScriptName)
		return new HHCameraMoveScript;
	if (L"HHLevelBackgroundScript" == _strScriptName)
		return new HHLevelBackgroundScript;
	if (L"HHMouseCursorScript" == _strScriptName)
		return new HHMouseCursorScript;
	if (L"HHPlayerScript" == _strScriptName)
		return new HHPlayerScript;
	if (L"HHSmallGirlScript" == _strScriptName)
		return new HHSmallGirlScript;
	if (L"HHTilemapScript" == _strScriptName)
		return new HHTilemapScript;
	if (L"HHTitleLogoScript" == _strScriptName)
		return new HHTitleLogoScript;
	return nullptr;
}

HHScript * HHScriptMgr::GetScript(UINT _iScriptType)
{
	switch (_iScriptType)
	{
	case (UINT)SCRIPT_TYPE::BUTTONSCRIPT:
		return new HHButtonScript;
		break;
	case (UINT)SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return new HHCameraMoveScript;
		break;
	case (UINT)SCRIPT_TYPE::LEVELBACKGROUNDSCRIPT:
		return new HHLevelBackgroundScript;
		break;
	case (UINT)SCRIPT_TYPE::MOUSECURSORSCRIPT:
		return new HHMouseCursorScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new HHPlayerScript;
		break;
	case (UINT)SCRIPT_TYPE::SMALLGIRLSCRIPT:
		return new HHSmallGirlScript;
		break;
	case (UINT)SCRIPT_TYPE::TILEMAPSCRIPT:
		return new HHTilemapScript;
		break;
	case (UINT)SCRIPT_TYPE::TITLELOGOSCRIPT:
		return new HHTitleLogoScript;
		break;
	}
	return nullptr;
}

const wchar_t * HHScriptMgr::GetScriptName(HHScript * _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
	case SCRIPT_TYPE::BUTTONSCRIPT:
		return L"HHButtonScript";
		break;

	case SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return L"HHCameraMoveScript";
		break;

	case SCRIPT_TYPE::LEVELBACKGROUNDSCRIPT:
		return L"HHLevelBackgroundScript";
		break;

	case SCRIPT_TYPE::MOUSECURSORSCRIPT:
		return L"HHMouseCursorScript";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"HHPlayerScript";
		break;

	case SCRIPT_TYPE::SMALLGIRLSCRIPT:
		return L"HHSmallGirlScript";
		break;

	case SCRIPT_TYPE::TILEMAPSCRIPT:
		return L"HHTilemapScript";
		break;

	case SCRIPT_TYPE::TITLELOGOSCRIPT:
		return L"HHTitleLogoScript";
		break;

	}
	return nullptr;
}