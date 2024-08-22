#include "pch.h"
#include "HHGameObjectEx.h"

#include <Engine/components.h>

void HHGameObjectEx::FinalTick()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != GetComponent((COMPONENT_TYPE)i))
			GetComponent((COMPONENT_TYPE)i)->FinalTick();
	}

	// 자식 오브젝트
	vector<HHGameObject*>::const_iterator iter = GetChildObjects().begin();
	for (; iter != GetChildObjects().end(); ++iter)
	{
		(*iter)->FinalTick();
	}
}
