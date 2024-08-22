#include "pch.h"
#include "HHMaterial.h"

#include "HHDevice.h"
#include "HHConstantBuffer.h"

#include "HHAssetMgr.h"
#include "HHPathMgr.h"

HHMaterial::HHMaterial(bool _IsEngineAsset)
	: HHAsset(ASSET_TYPE::MATERIAL)
{
	if (_IsEngineAsset)
	{
		SetEngineAsset();
	}
}

HHMaterial::~HHMaterial()
{
}

void HHMaterial::Binding()
{
	if (!m_Shader)
		return;

	for (int i = 0; i < TEXTURE_PARAM::END; ++i)
	{
		if (nullptr == m_arrTex[i])
		{
			m_MaterialConst.btex[i] = 0;
			HHTexture::Clear(i);
			continue;
		}

		m_MaterialConst.btex[i] = 1;
		m_arrTex[i]->Binding(i);
	}

	HHConstantBuffer* pCB = HHDevice::GetInstance()->GetConstantBuffer(CONSTANT_BUFFER_TYPE::MATERIAL);
	pCB->SetData(&m_MaterialConst);
	pCB->Binding();

	m_Shader->Binding();
}

void* HHMaterial::GetScalarParam(SCALAR_PARAM _Param)
{
	switch (_Param)
	{
	case INT_0:
	case INT_1:
	case INT_2:
	case INT_3:
		return  m_MaterialConst.iArr + _Param;
		break;
	case FLOAT_0:
	case FLOAT_1:
	case FLOAT_2:
	case FLOAT_3:
		return  m_MaterialConst.fArr + (_Param - FLOAT_0);
		break;
	case VEC2_0:
	case VEC2_1:
	case VEC2_2:
	case VEC2_3:
		return  m_MaterialConst.v2Arr + (_Param - VEC2_0);
		break;
	case VEC4_0:
	case VEC4_1:
	case VEC4_2:
	case VEC4_3:
		return  m_MaterialConst.v4Arr + (_Param - VEC4_0);
		break;
	case MAT_0:
	case MAT_1:
	case MAT_2:
	case MAT_3:
		return  m_MaterialConst.matArr + (_Param - MAT_0);
		break;
	}

	return nullptr;
}

int HHMaterial::Save(const wstring& _RelativePath)
{
	SetRelativePath(_RelativePath);

	wstring strFilePath = HHPathMgr::GetInstance()->GetContentPath();
	strFilePath += _RelativePath;

	FILE* File = nullptr;
	_wfopen_s(&File, strFilePath.c_str(), L"wb");

	if (nullptr == File)
		return E_FAIL;

	// 어떤 쉐이더를 참조했는지
	SaveAssetReference(m_Shader, File);

	// 상수 데이터
	fwrite(&m_MaterialConst, sizeof(tMaterialConstant), 1, File);

	for (UINT i = 0; i < TEXTURE_PARAM::END; ++i)
	{
		SaveAssetReference(m_arrTex[i], File);
	}

	fclose(File);

	return S_OK;
}

int HHMaterial::Load(const wstring& _FilePath)
{
	FILE* File = nullptr;
	_wfopen_s(&File, _FilePath.c_str(), L"rb");

	if (nullptr == File)
		return E_FAIL;

	// 어떤 쉐이더를 참조했는지
	LoadAssetReference(m_Shader, File);

	// 상수 데이터
	fread(&m_MaterialConst, sizeof(tMaterialConstant), 1, File);

	for (UINT i = 0; i < TEXTURE_PARAM::END; ++i)
	{
		LoadAssetReference(m_arrTex[i], File);
	}

	fclose(File);

	return S_OK;
}
