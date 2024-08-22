#include "pch.h"
#include "HHScriptMgr.h"

#include "HHCameraMoveScript.h"
#include "HHMissileScript.h"
#include "HHPlayerScript.h"

void HHScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"HHCameraMoveScript");
	_vec.push_back(L"HHMissileScript");
	_vec.push_back(L"HHPlayerScript");
}

HHScript * HHScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"HHCameraMoveScript" == _strScriptName)
		return new HHCameraMoveScript;
	if (L"HHMissileScript" == _strScriptName)
		return new HHMissileScript;
	if (L"HHPlayerScript" == _strScriptName)
		return new HHPlayerScript;
	return nullptr;
}

HHScript * HHScriptMgr::GetScript(UINT _iScriptType)
{
	switch (_iScriptType)
	{
	case (UINT)SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return new HHCameraMoveScript;
		break;
	case (UINT)SCRIPT_TYPE::MISSILESCRIPT:
		return new HHMissileScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new HHPlayerScript;
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

	case SCRIPT_TYPE::MISSILESCRIPT:
		return L"HHMissileScript";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"HHPlayerScript";
		break;

	}
	return nullptr;
}