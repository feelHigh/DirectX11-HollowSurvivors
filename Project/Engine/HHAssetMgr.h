#pragma once
#include "HHPathMgr.h"
#include "HHTaskMgr.h"

class HHAsset;

class HHAssetMgr
	: public HHSingleton<HHAssetMgr>
{
	SINGLE(HHAssetMgr);

public:
	void Initialize();
	void Tick();

	template<typename T>
	Ptr<T> Load(const wstring& _Key, const wstring& _RelativePath);

	Ptr<HHAsset> FindAsset(ASSET_TYPE _Type, const wstring& _Key);
	//void AddAsset(const wstring& _Key, CAsset* _Asset);

	template<typename T>
	Ptr<T> FindAsset(const wstring& _Key);

	template<typename T>
	void AddAsset(const wstring& _Key, Ptr<T> _Asset);
	//void DeleteAsset(ASSET_TYPE _type, const wstring& _strKey);

	void GetAssetNames(ASSET_TYPE _Type, vector<string>& _vecOut);
	const map<wstring, Ptr<HHAsset>>& GetAssets(ASSET_TYPE _Type) { return m_mapAsset[(UINT)_Type]; }

	bool IsChanged() { return m_Changed; }

	// _Flags : D3D11_BIND_FLAG
	Ptr<HHTexture> CreateTexture(wstring _strKey, UINT _Width, UINT _Height
								, DXGI_FORMAT _Format, UINT _Flags
								, D3D11_USAGE _Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT);

	Ptr<HHTexture> CreateTexture(wstring _strKey, ComPtr<ID3D11Texture2D> _Tex2D);

private:
	friend class HHTaskMgr;

	map<wstring, Ptr<HHAsset>>	m_mapAsset[(UINT)ASSET_TYPE::END];
	bool						m_Changed;

	void DeleteAsset(ASSET_TYPE _Type, const wstring& _Key);

	void CreateEngineMesh();
	void CreateEngineMaterial();
	void CreateEngineTexture();
	void CreateEngineSprite();
	void CreateEngineGraphicShader();
	void CreateEngineComputeShader();

};

template<typename T>
Ptr<T> HHAssetMgr::Load(const wstring& _Key, const wstring& _RelativePath)
{
	// ���� Ű�� ������ �ִ��� Ȯ��
	Ptr<T> Asset = FindAsset<T>(_Key);

	if (nullptr != Asset)
	{
		return Asset;
	}

	// ���� Ű���� ������ ��������
	wstring strFilePath = HHPathMgr::GetInstance()->GetContentPath();
	strFilePath += _RelativePath;

	Asset = new T;

	// �ε� ���� �� ����ó��
	if (FAILED(Asset->Load(strFilePath)))
	{
		MessageBox(nullptr, L"���� �ε� ����", L"�ε� ����", MB_OK);
		return nullptr;
	}

	// Asset �� �ڽ��� Ű���� ��θ� �˰� ��
	Asset->m_Key = _Key;
	Asset->m_RelativePath = _RelativePath;

	// �ʿ� ���
	ASSET_TYPE type = GetAssetType<T>();
	m_mapAsset[(UINT)type].insert(make_pair(_Key, Asset.Get()));

	// Asset ���� �˸�	
	HHTaskMgr::GetInstance()->AddTask(tTask{ ASSET_CHANGED });

	// �ε��� ���� �ּ� ��ȯ
	return Asset;
}

template<typename T>
Ptr<T> HHAssetMgr::FindAsset(const wstring& _Key)
{
	ASSET_TYPE Type = GetAssetType<T>();

	map<wstring, Ptr<HHAsset>>::iterator iter = m_mapAsset[(UINT)Type].find(_Key);

	if (iter == m_mapAsset[(UINT)Type].end())
		return nullptr;

	//Ptr<HHAsset> pAsset;
	//Ptr<HHMesh> pMesh = (HHMesh*)pAsset.Get()

	return (T*)iter->second.Get();
}

template<typename T>
void HHAssetMgr::AddAsset(const wstring& _Key, Ptr<T> _Asset)
{
	ASSET_TYPE Type = GetAssetType<T>();

	assert(!FindAsset(Type, _Key).Get());

	_Asset->SetKey(_Key);
	m_mapAsset[(UINT)Type].insert(make_pair(_Key, _Asset.Get()));

	// Asset ���� �˸�	
	HHTaskMgr::GetInstance()->AddTask(tTask{ ASSET_CHANGED });
}
/*
void HHAssetMgr::DeleteAsset(ASSET_TYPE _type, const wstring& _strKey)
{
	map<wstring, Ptr<HHAsset>>::iterator iter = m_mapAsset[(UINT)_type].find(_strKey);

	assert(!(iter == m_mapAsset[(UINT)_type].end()));

	m_mapAsset[(UINT)_type].erase(iter);
}
*/ 
// File �� Asset �������� ���� �ҷ�����
template<typename T>
void SaveAssetReference(Ptr<T> Asset, FILE* _File)
{
	bool bAsset = Asset.Get();
	fwrite(&bAsset, 1, 1, _File);

	if (bAsset)
	{
		SaveWString(Asset->GetKey(), _File);
		SaveWString(Asset->GetRelativePath(), _File);
	}
}

template<typename T>
void LoadAssetReference(Ptr<T>& Asset, FILE* _File)
{
	bool bAsset = false;
	fread(&bAsset, 1, 1, _File);

	if (bAsset)
	{
		wstring key, relativepath;
		LoadWString(key, _File);
		LoadWString(relativepath, _File);

		Asset = HHAssetMgr::GetInstance()->Load<T>(key, relativepath);
	}
}