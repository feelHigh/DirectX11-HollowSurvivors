#include "pch.h"
#include "HHSprite.h"

#include "HHAssetMgr.h"
#include "HHTexture.h"

HHSprite::HHSprite()
	: HHAsset(ASSET_TYPE::SPRITE)
{
}

HHSprite::~HHSprite()
{
}

void HHSprite::Create(Ptr<HHTexture> _Atlas, Vec2 _LeftTopPixel, Vec2 _SlicePixel)
{
	m_Atlas = _Atlas;
	assert(m_Atlas);

	UINT width = m_Atlas->Width();
	UINT height = m_Atlas->Height();

	m_LeftTopUV = Vec2(_LeftTopPixel.x / (float)width, _LeftTopPixel.y / (float)height);
	m_SliceUV = Vec2(_SlicePixel.x / (float)width, _SlicePixel.y / (float)height);
}

void HHSprite::SetLeftTop(Vec2 _LeftTop)
{
	Vec2 AtlasResolution = Vec2((float)m_Atlas->Width(), (float)m_Atlas->Height());
	m_LeftTopUV = _LeftTop / AtlasResolution;
}

void HHSprite::SetSlice(Vec2 _Slice)
{
	Vec2 AtlasResolution = Vec2((float)m_Atlas->Width(), (float)m_Atlas->Height());
	m_SliceUV = _Slice / AtlasResolution;
}

void HHSprite::SetBackground(Vec2 _Background)
{
	Vec2 AtlasResolution = Vec2((float)m_Atlas->Width(), (float)m_Atlas->Height());
	m_BackgroundUV = _Background / AtlasResolution;
}

void HHSprite::SetOffset(Vec2 _Offset)
{
	Vec2 AtlasResolution = Vec2((float)m_Atlas->Width(), (float)m_Atlas->Height());
	m_OffsetUV = _Offset / AtlasResolution;
}

int HHSprite::Save(const wstring& _FilePath)
{
	FILE* File = nullptr;
	_wfopen_s(&File, _FilePath.c_str(), L"wb");

	if (nullptr == File)
		return E_FAIL;

	// Atlas 참조정보 저장
	SaveAssetReference(m_Atlas, File);

	fwrite(&m_LeftTopUV, sizeof(Vec2), 1, File);
	fwrite(&m_SliceUV, sizeof(Vec2), 1, File);
	fwrite(&m_BackgroundUV, sizeof(Vec2), 1, File);
	fwrite(&m_OffsetUV, sizeof(Vec2), 1, File);

	fclose(File);

	return S_OK;
}

int HHSprite::Load(const wstring& _FilePath)
{
	FILE* File = nullptr;
	_wfopen_s(&File, _FilePath.c_str(), L"rb");

	if (nullptr == File)
	{
		return E_FAIL;
	}

	// Atlas 키, 경로 불러오기
	LoadAssetReference(m_Atlas, File);

	fread(&m_LeftTopUV, sizeof(Vec2), 1, File);
	fread(&m_SliceUV, sizeof(Vec2), 1, File);
	fread(&m_BackgroundUV, sizeof(Vec2), 1, File);
	fread(&m_OffsetUV, sizeof(Vec2), 1, File);

	fclose(File);

	return S_OK;
}
