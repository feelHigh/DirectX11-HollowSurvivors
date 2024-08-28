#include "pch.h"
#include "HHScriptMgr.h"

#include "HHCameraMoveScript.h"
#include "HHMenuButtonScript.h"
#include "HHPlayerScript.h"
#include "HHSmallGirlScript.h"

void HHScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"HHCameraMoveScript");
	_vec.push_back(L"HHMenuButtonScript");
	_vec.push_back(L"HHPlayerScript");
	_vec.push_back(L"HHSmallGirlScript");
}

HHScript * HHScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"HHCameraMoveScript" == _strScriptName)
		return new HHCameraMoveScript;
	if (L"HHMenuButtonScript" == _strScriptName)
		return new HHMenuButtonScript;
	if (L"HHPlayerScript" == _strScriptName)
		return new HHPlayerScript;
	if (L"HHSmallGirlScript" == _strScriptName)
		return new HHSmallGirlScript;
	return nullptr;
}

HHScript * HHScriptMgr::GetScript(UINT _iScriptType)
{
	switch (_iScriptType)
	{
	case (UINT)SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return new HHCameraMoveScript;
		break;
	case (UINT)SCRIPT_TYPE::MENUBUTTONSCRIPT:
		return new HHMenuButtonScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new HHPlayerScript;
		break;
	case (UINT)SCRIPT_TYPE::SMALLGIRLSCRIPT:
		return new HHSmallGirlScript;
		break;
	}
	return nullptr;
}

const wchar_t * HHScriptMgr::GetScriptName(HHScript * _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
	case SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return L"HHCameraMoveScript";
		break;

	case SCRIPT_TYPE::MENUBUTTONSCRIPT:
		return L"HHMenuButtonScript";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"HHPlayerScript";
		break;

	case SCRIPT_TYPE::SMALLGIRLSCRIPT:
		return L"HHSmallGirlScript";
		break;

	}
	return nullptr;
}