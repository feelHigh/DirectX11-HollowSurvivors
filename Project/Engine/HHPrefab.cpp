#include "pch.h"
#include "HHPrefab.h"
#include "HHGameObject.h"

OBJECT_SAVE  HHPrefab::g_ObjectSaveFunc = nullptr;
OBJECT_LOAD  HHPrefab::g_ObjectLoadFunc = nullptr;

HHPrefab::HHPrefab()
	: HHAsset(ASSET_TYPE::PREFAB)
	, m_ProtoObject(nullptr)
{
}

HHPrefab::~HHPrefab()
{
	if (nullptr != m_ProtoObject)
		delete m_ProtoObject;
}

HHGameObject* HHPrefab::Instantiate()
{
	return m_ProtoObject->Clone();
}

int HHPrefab::Load(const wstring& _FilePath)
{
    FILE* File = nullptr;
    _wfopen_s(&File, _FilePath.c_str(), L"rb");

    if (nullptr == File)
        return E_FAIL;

    m_ProtoObject = g_ObjectLoadFunc(File);

    fclose(File);

    return S_OK;
}

int HHPrefab::Save(const wstring& _FilePath)
{
    FILE* File = nullptr;
    _wfopen_s(&File, _FilePath.c_str(), L"wb");

    if (nullptr == File)
        return E_FAIL;

    g_ObjectSaveFunc(File, m_ProtoObject);

    fclose(File);

    return S_OK;
}
