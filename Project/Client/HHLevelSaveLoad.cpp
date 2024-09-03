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

	// Level �̸� ����
	SaveWString(_Level->GetName(), File);

	// Level �ȿ� �ִ� Layer �� ����
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		HHLayer* pLayer = _Level->GetLayer(i);

		// Layer �̸� ����
		SaveWString(pLayer->GetName(), File);

		// Layer �ȿ� �ִ� GameObject �� ����
		const vector<HHGameObject*>& vecParents = pLayer->GetParentObjects();

		// Layer �� ������ ParentObject ���� ����
		size_t count = vecParents.size();
		fwrite(&count, sizeof(size_t), 1, File);

		// GameObject ����
		for (size_t i = 0; i < vecParents.size(); ++i)
		{
			SaveGameObject(File, vecParents[i]);
		}
	}

	fclose(File);
}

void HHLevelSaveLoad::SaveGameObject(FILE* _File, HHGameObject* _Object)
{
	// GameObject �� �̸� ����
	SaveWString(_Object->GetName(), _File);

	// Component ���� ����
	UINT i = 0;
	for (; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		HHComponent* pComponent = _Object->GetComponent((COMPONENT_TYPE)i);

		if (nullptr == pComponent)
			continue;

		// ComponentType �� ����
		COMPONENT_TYPE Type = pComponent->GetComponentType();
		fwrite(&Type, sizeof(COMPONENT_TYPE), 1, _File);

		pComponent->SaveToFile(_File);
	}

	// COMPONENT_TYPE::END ����
	fwrite(&i, sizeof(COMPONENT_TYPE), 1, _File);

	// Script ���� ����
	// Script ���� ����
	const vector<HHScript*> vecScripts = _Object->GetScripts();
	size_t ScriptCount = vecScripts.size();
	fwrite(&ScriptCount, sizeof(size_t), 1, _File);

	for (size_t i = 0; i < ScriptCount; ++i)
	{
		// Script �� �̸� ����
		wstring ScriptName = HHScriptMgr::GetScriptName(vecScripts[i]);
		SaveWString(ScriptName, _File);

		// Script ���� ����
		vecScripts[i]->SaveToFile(_File);
	}

	// Child ���� ����
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

	// Level ����
	HHLevel* pNewLevel = new HHLevel;

	// Level �̸� �ҷ�����
	wstring LevelName;
	LoadWString(LevelName, File);
	pNewLevel->SetName(LevelName);

	// Level �ȿ� �ִ� Layer ���� �ҷ�����
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		HHLayer* pLayer = pNewLevel->GetLayer(i);

		// Layer �̸� �ҷ�����
		wstring LayerName;
		LoadWString(LayerName, File);
		pLayer->SetName(LayerName);

		// Layer �� ������ ParentObject ���� �Ҿ����
		size_t count = 0;
		fread(&count, sizeof(size_t), 1, File);

		// GameObject �ҷ��ͼ� Layer �� ����ֱ�
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

	// GameObject �� �̸� �ε�
	wstring Name;
	LoadWString(Name, _File);
	pObject->SetName(Name);

	// Component ���� �ε�	
	COMPONENT_TYPE Type = COMPONENT_TYPE::END;
	while (true)
	{
		// ����Ǿ��ִ� ������ � ������Ʈ���� Ȯ��
		fread(&Type, sizeof(COMPONENT_TYPE), 1, _File);

		// ���� Ÿ�� ������ END �� ���, ����� ������Ʈ ������ ���̴�.
		if (COMPONENT_TYPE::END == Type)
			break;

		// ����� Ÿ�Կ� �´� ������Ʈ�� ���� ��Ű��, �����Ҷ��� ������ ������ �����͸� �д´�.
		HHComponent* pComponent = GetComponent(Type);

		// ������ ������Ʈ�� ������Ʈ�� �־��ش�.
		pObject->AddComponent(pComponent);

		// �������� ������ �о�ͼ� �����Ѵ�.
		pComponent->LoadFromFile(_File);
	}

	// Script ���� �ε�	
	size_t ScriptCount = 0;
	fread(&ScriptCount, sizeof(size_t), 1, _File);

	for (size_t i = 0; i < ScriptCount; ++i)
	{
		// Script �� �̸� �б�
		wstring ScriptName;
		LoadWString(ScriptName, _File);

		// ���� Script �̸����� �̸��� �ش��ϴ� Script ����
		HHScript* pScript = HHScriptMgr::GetScript(ScriptName);
		pScript->LoadFromFile(_File);

		pObject->AddComponent(pScript);
	}

	// Child ���� �ε�
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
