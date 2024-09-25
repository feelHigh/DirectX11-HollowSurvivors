#include "pch.h"
#include "HHScriptMgr.h"

#include "HHButtonScript.h"
#include "HHCameraMoveScript.h"
#include "HHMouseCursorScript.h"
#include "HHPlayerCameraScript.h"
#include "HHPlayerScript.h"
#include "HHSmallGirlScript.h"
#include "HHTilemapScript.h"
#include "HHTitleBackgroundScript.h"
#include "HHTitleLogoScript.h"
#include "HHTutorialBackgroundCloudScript.h"
#include "HHTutorialBackgroundScript.h"
#include "HHTutorialMapScript.h"

void HHScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"HHButtonScript");
	_vec.push_back(L"HHCameraMoveScript");
	_vec.push_back(L"HHMouseCursorScript");
	_vec.push_back(L"HHPlayerCameraScript");
	_vec.push_back(L"HHPlayerScript");
	_vec.push_back(L"HHSmallGirlScript");
	_vec.push_back(L"HHTilemapScript");
	_vec.push_back(L"HHTitleBackgroundScript");
	_vec.push_back(L"HHTitleLogoScript");
	_vec.push_back(L"HHTutorialBackgroundCloudScript");
	_vec.push_back(L"HHTutorialBackgroundScript");
	_vec.push_back(L"HHTutorialMapScript");
}

HHScript * HHScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"HHButtonScript" == _strScriptName)
		return new HHButtonScript;
	if (L"HHCameraMoveScript" == _strScriptName)
		return new HHCameraMoveScript;
	if (L"HHMouseCursorScript" == _strScriptName)
		return new HHMouseCursorScript;
	if (L"HHPlayerCameraScript" == _strScriptName)
		return new HHPlayerCameraScript;
	if (L"HHPlayerScript" == _strScriptName)
		return new HHPlayerScript;
	if (L"HHSmallGirlScript" == _strScriptName)
		return new HHSmallGirlScript;
	if (L"HHTilemapScript" == _strScriptName)
		return new HHTilemapScript;
	if (L"HHTitleBackgroundScript" == _strScriptName)
		return new HHTitleBackgroundScript;
	if (L"HHTitleLogoScript" == _strScriptName)
		return new HHTitleLogoScript;
	if (L"HHTutorialBackgroundCloudScript" == _strScriptName)
		return new HHTutorialBackgroundCloudScript;
	if (L"HHTutorialBackgroundScript" == _strScriptName)
		return new HHTutorialBackgroundScript;
	if (L"HHTutorialMapScript" == _strScriptName)
		return new HHTutorialMapScript;
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
	case (UINT)SCRIPT_TYPE::MOUSECURSORSCRIPT:
		return new HHMouseCursorScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERCAMERASCRIPT:
		return new HHPlayerCameraScript;
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
	case (UINT)SCRIPT_TYPE::TITLEBACKGROUNDSCRIPT:
		return new HHTitleBackgroundScript;
		break;
	case (UINT)SCRIPT_TYPE::TITLELOGOSCRIPT:
		return new HHTitleLogoScript;
		break;
	case (UINT)SCRIPT_TYPE::TUTORIALBACKGROUNDCLOUDSCRIPT:
		return new HHTutorialBackgroundCloudScript;
		break;
	case (UINT)SCRIPT_TYPE::TUTORIALBACKGROUNDSCRIPT:
		return new HHTutorialBackgroundScript;
		break;
	case (UINT)SCRIPT_TYPE::TUTORIALMAPSCRIPT:
		return new HHTutorialMapScript;
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

	case SCRIPT_TYPE::MOUSECURSORSCRIPT:
		return L"HHMouseCursorScript";
		break;

	case SCRIPT_TYPE::PLAYERCAMERASCRIPT:
		return L"HHPlayerCameraScript";
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

	case SCRIPT_TYPE::TITLEBACKGROUNDSCRIPT:
		return L"HHTitleBackgroundScript";
		break;

	case SCRIPT_TYPE::TITLELOGOSCRIPT:
		return L"HHTitleLogoScript";
		break;

	case SCRIPT_TYPE::TUTORIALBACKGROUNDCLOUDSCRIPT:
		return L"HHTutorialBackgroundCloudScript";
		break;

	case SCRIPT_TYPE::TUTORIALBACKGROUNDSCRIPT:
		return L"HHTutorialBackgroundScript";
		break;

	case SCRIPT_TYPE::TUTORIALMAPSCRIPT:
		return L"HHTutorialMapScript";
		break;

	}
	return nullptr;
}