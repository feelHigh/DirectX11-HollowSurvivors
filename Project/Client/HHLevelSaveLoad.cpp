#include "pch.h"
#include "HHLevelSaveLoad.h"

#include <Engine/HHLevelMgr.h>
#include <Engine/HHLevel.h>
#include <Engine/HHLayer.h>
#include <Engine/HHGameObject.h>
#include <Engine/components.h>

#include <Scripts/HHScriptMgr.h>

void HHLevelSaveLoad::SaveLevel(const wstring& _FilePath, HHLevel* _Level)
{
	assert(_Level && _Level->GetState() == LEVEL_STATE::STOP);

	FILE* File = nullptr;
	_wfopen_s(&File, _FilePath.c_str(), L"wb");

	// Level 이름 저장
	SaveWString(_Level->GetName(), File);

	// Level 안에 있는 Layer 를 저장
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		HHLayer* pLayer = _Level->GetLayer(i);

		// Layer 이름 저장
		SaveWString(pLayer->GetName(), File);

		// Layer 안에 있는 GameObject 를 저장
		const vector<HHGameObject*>& vecParents = pLayer->GetParentObjects();

		// Layer 가 보유한 ParentObject 개수 저장
		size_t count = vecParents.size();
		fwrite(&count, sizeof(size_t), 1, File);

		// GameObject 저장
		for (size_t i = 0; i < vecParents.size(); ++i)
		{
			SaveGameObject(File, vecParents[i]);
		}
	}

	fclose(File);
}

void HHLevelSaveLoad::SaveGameObject(FILE* _File, HHGameObject* _Object)
{
	// GameObject 의 이름 저장
	SaveWString(_Object->GetName(), _File);

	// Component 정보 저장
	UINT i = 0;
	for (; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		HHComponent* pComponent = _Object->GetComponent((COMPONENT_TYPE)i);

		if (nullptr == pComponent)
			continue;

		// ComponentType 을 저장
		COMPONENT_TYPE Type = pComponent->GetComponentType();
		fwrite(&Type, sizeof(COMPONENT_TYPE), 1, _File);

		pComponent->SaveToFile(_File);
	}

	// COMPONENT_TYPE::END 저장
	fwrite(&i, sizeof(COMPONENT_TYPE), 1, _File);

	// Script 정보 저장
	// Script 개수 저장
	const vector<HHScript*> vecScripts = _Object->GetScripts();
	size_t ScriptCount = vecScripts.size();
	fwrite(&ScriptCount, sizeof(size_t), 1, _File);

	for (size_t i = 0; i < ScriptCount; ++i)
	{
		// Script 의 이름 저장
		wstring ScriptName = HHScriptMgr::GetScriptName(vecScripts[i]);
		SaveWString(ScriptName, _File);

		// Script 정보 저장
		vecScripts[i]->SaveToFile(_File);
	}

	// Child 정보 저장
	const vector<HHGameObject*>& vecChild = _Object->GetChildObjects();
	size_t ChildCount = vecChild.size();
	fwrite(&ChildCount, sizeof(size_t), 1, _File);

	for (size_t i = 0; i < vecChild.size(); ++i)
	{
		SaveGameObject(_File, vecChild[i]);
	}
}

HHLevel* HHLevelSaveLoad::LoadLevel(const wstring& _FilePath)
{
	FILE* File = nullptr;
	_wfopen_s(&File, _FilePath.c_str(), L"rb");

	// Level 생성
	HHLevel* pNewLevel = new HHLevel;

	// Level 이름 불러오기
	wstring LevelName;
	LoadWString(LevelName, File);
	pNewLevel->SetName(LevelName);

	// Level 안에 있는 Layer 정보 불러오기
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		HHLayer* pLayer = pNewLevel->GetLayer(i);

		// Layer 이름 불러오기
		wstring LayerName;
		LoadWString(LayerName, File);
		pLayer->SetName(LayerName);

		// Layer 가 보유한 ParentObject 개수 불어오기
		size_t count = 0;
		fread(&count, sizeof(size_t), 1, File);

		// GameObject 불러와서 Layer 에 집어넣기
		for (size_t i = 0; i < count; ++i)
		{
			HHGameObject* pLoadedObject = LoadGameObject(File);
			pLayer->AddObject(pLoadedObject, false);
		}
	}

	fclose(File);

	return pNewLevel;
}

HHGameObject* HHLevelSaveLoad::LoadGameObject(FILE* _File)
{
	HHGameObject* pObject = new HHGameObject;

	// GameObject 의 이름 로드
	wstring Name;
	LoadWString(Name, _File);
	pObject->SetName(Name);

	// Component 정보 로드	
	COMPONENT_TYPE Type = COMPONENT_TYPE::END;
	while (true)
	{
		// 저장되어있는 정보가 어떤 컴포넌트인지 확인
		fread(&Type, sizeof(COMPONENT_TYPE), 1, _File);

		// 읽은 타입 정보가 END 인 경우, 저장된 컴포넌트 정보의 끝이다.
		if (COMPONENT_TYPE::END == Type)
			break;

		// 저장된 타입에 맞는 컴포넌트를 생성 시키고, 저장할때랑 동일한 순서로 데이터를 읽는다.
		HHComponent* pComponent = GetComponent(Type);

		// 생성된 컴포넌트를 오브젝트에 넣어준다.
		pObject->AddComponent(pComponent);

		// 저장당시의 정보를 읽어와서 복수한다.
		pComponent->LoadFromFile(_File);
	}

	// Script 정보 로드	
	size_t ScriptCount = 0;
	fread(&ScriptCount, sizeof(size_t), 1, _File);

	for (size_t i = 0; i < ScriptCount; ++i)
	{
		// Script 의 이름 읽기
		wstring ScriptName;
		LoadWString(ScriptName, _File);

		// 읽은 Script 이름으로 이름에 해당하는 Script 생성
		HHScript* pScript = HHScriptMgr::GetScript(ScriptName);
		pScript->LoadFromFile(_File);

		pObject->AddComponent(pScript);
	}

	// Child 정보 로드
	size_t ChildCount = 0;
	fread(&ChildCount, sizeof(size_t), 1, _File);

	for (size_t i = 0; i < ChildCount; ++i)
	{
		HHGameObject* pChildObject = LoadGameObject(_File);
		pObject->AddChild(pChildObject);
	}

	return pObject;
}

HHComponent* HHLevelSaveLoad::GetComponent(COMPONENT_TYPE _Type)
{
	switch (_Type)
	{
	case COMPONENT_TYPE::TRANSFORM:
		return new HHTransform;

	case COMPONENT_TYPE::COLLIDER2D:
		return new HHCollider2D;

	case COMPONENT_TYPE::COLLIDER3D:

		break;
	case COMPONENT_TYPE::LIGHT2D:
		return  new HHLight2D;

	case COMPONENT_TYPE::LIGHT3D:
		break;

	case COMPONENT_TYPE::FLIPBOOK_RENDERER:
		return new HHFlipbookRenderer;

	case COMPONENT_TYPE::ANIMATOR3D:
		break;

	case COMPONENT_TYPE::STATE_MACHINE:
		break;

	case COMPONENT_TYPE::RIGIDBODY:
		break;

	case COMPONENT_TYPE::CAMERA:
		return  new HHCamera;

	case COMPONENT_TYPE::MESHRENDER:
		return  new HHMeshRender;

	case COMPONENT_TYPE::TILEMAP:
		return  new HHTilemap;

	case COMPONENT_TYPE::PARTICLESYSTEM:
		break;

	case COMPONENT_TYPE::DECAl:
		break;

	case COMPONENT_TYPE::SKYBOX:
		break;

	case COMPONENT_TYPE::LANDSCAPE:
		break;

	case COMPONENT_TYPE::TEXTRENDERER:
		return new HHTextRenderer;

	case COMPONENT_TYPE::GAME_TEXT:
		return new HHText;

	/*case COMPONENT_TYPE::GAME_BUTTON:
		return new HHButton;*/

	}

	return nullptr;
}
