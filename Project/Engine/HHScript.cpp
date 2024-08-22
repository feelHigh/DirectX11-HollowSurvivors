#include "pch.h"
#include "HHScript.h"

HHScript::HHScript(UINT _ScriptType)
	: HHComponent(COMPONENT_TYPE::SCRIPT)
	, m_ScriptType(_ScriptType)
{
}

HHScript::~HHScript()
{
}

void HHScript::Instantiate(Ptr<HHPrefab> _Pref, int _LayerIdx, Vec3 _WorldPos, const wstring& _Name)
{
	HHGameObject* pInst = _Pref->Instantiate();

	pInst->SetName(_Name);
	pInst->Transform()->SetRelativePosition(_WorldPos);

	CreateObject(pInst, _LayerIdx);
}
