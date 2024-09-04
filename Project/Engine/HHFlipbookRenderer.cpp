#include "pch.h"
#include "HHFlipbookRenderer.h"

#include "HHDevice.h"
#include "HHConstantBuffer.h"
#include "HHTimeMgr.h"
#include "HHAssetMgr.h"

#include "HHFlipbook.h"

HHFlipbookRenderer::HHFlipbookRenderer()
	: HHComponent(COMPONENT_TYPE::FLIPBOOK_RENDERER)
{
}

HHFlipbookRenderer::HHFlipbookRenderer(HHFlipbookRenderer& _Origin)
	: HHComponent(_Origin)
	, m_vecFlipbook(_Origin.m_vecFlipbook)
	, m_CurFlipbook(_Origin.m_CurFlipbook)
	, m_CurFrmIdx(0)
	, m_FPS(_Origin.m_FPS)
	, m_AccTime(0.f)
	, m_Repeat(_Origin.m_Repeat)
	, m_Finish(false)
{
	if (nullptr != m_CurFlipbook)
	{
		int FlipBookIdx = 0;
		for (; FlipBookIdx < (int)m_vecFlipbook.size(); ++FlipBookIdx)
		{
			if (m_CurFlipbook == m_vecFlipbook[FlipBookIdx])
				break;
		}

		Play(FlipBookIdx, m_FPS, m_Repeat);
	}
}

HHFlipbookRenderer::~HHFlipbookRenderer()
{
}

void HHFlipbookRenderer::FinalTick()
{
	if (m_Finish)
	{
		if (false == m_Repeat)
			return;

		Reset();
	}

	if (nullptr != m_CurFlipbook)
	{
		float MaxTime = 1.f / m_FPS;

		m_AccTime += DT;

		if (MaxTime < m_AccTime)
		{
			m_AccTime -= MaxTime;
			++m_CurFrmIdx;

			if (m_CurFlipbook->GetMaxFrameCount() <= m_CurFrmIdx)
			{
				--m_CurFrmIdx;
				m_Finish = true;
			}
		}

		m_CurFrmSprite = m_CurFlipbook->GetSprite(m_CurFrmIdx);
	}
}

void HHFlipbookRenderer::AddFlipbook(int _Idx, Ptr<HHFlipbook> _Flipbook)
{
	if (m_vecFlipbook.size() <= _Idx)
	{
		m_vecFlipbook.resize(_Idx + 1);
	}

	m_vecFlipbook[_Idx] = _Flipbook;
}

Ptr<HHFlipbook> HHFlipbookRenderer::FindFlipbook(const wstring& _Key)
{
	for (size_t i = 0; i < m_vecFlipbook.size(); ++i)
	{
		if (m_vecFlipbook[i]->GetKey() == _Key)
			return m_vecFlipbook[i];
	}

	return nullptr;
}

void HHFlipbookRenderer::Play(int _FlipbookIndex, float _FPS, bool _Repeat)
{
	m_CurFlipbook = m_vecFlipbook[_FlipbookIndex];

	if (nullptr == m_CurFlipbook)
	{
		return;
	}

	m_CurFrmIdx = 0;
	m_AccTime = 0.f;
	m_FPS = _FPS;
	m_Repeat = _Repeat;
}

void HHFlipbookRenderer::Reset()
{
	m_CurFrmIdx = 0;
	m_AccTime = 0.f;
	m_Finish = false;
}

void HHFlipbookRenderer::Binding()
{
	if (nullptr != m_CurFrmSprite)
	{
		// ���� ǥ���ؾ��ϴ� Sprite �� ������ Sprite ���� ������۸� ���ؼ� GPU �� ����
		tSpriteInfo tInfo = {};

		tInfo.LeftTopUV = m_CurFrmSprite->GetLeftTopUV();
		tInfo.SliceUV = m_CurFrmSprite->GetSliceUV();
		tInfo.BackGroundUV = m_CurFrmSprite->GetBackgroundUV();
		tInfo.OffsetUV = m_CurFrmSprite->GetOffsetUV();
		tInfo.UseFlipbook = 1;

		static HHConstantBuffer* CB = HHDevice::GetInstance()->GetConstantBuffer(CONSTANT_BUFFER_TYPE::SPRITE);

		CB->SetData(&tInfo);
		CB->Binding();

		// FlipBook Sprite ��Ʋ�� �ؽ��� ���� �������͹�ȣ t10 �� ���ε�
		Ptr<HHTexture> pAtlas = m_CurFrmSprite->GetAtlasTexture();
		pAtlas->Binding(10);
	}
	else
	{
		Clear();
	}
}

void HHFlipbookRenderer::Clear()
{
	tSpriteInfo tInfo = {};
	static HHConstantBuffer* CB = HHDevice::GetInstance()->GetConstantBuffer(CONSTANT_BUFFER_TYPE::SPRITE);
	CB->SetData(&tInfo);
	CB->Binding();
}

void HHFlipbookRenderer::SaveToFile(FILE* _File)
{
	// FlipBook ���� ��� ����
	size_t FlipBookCount = m_vecFlipbook.size();
	fwrite(&FlipBookCount, sizeof(size_t), 1, _File);
	for (size_t i = 0; i < m_vecFlipbook.size(); ++i)
	{
		SaveAssetReference(m_vecFlipbook[i], _File);
	}

	// ���� ������� FlipBook ���� ����
	SaveAssetReference(m_CurFlipbook, _File);

	// ���� ������� FlipBook ������ ������ Sprite
	SaveAssetReference(m_CurFrmSprite, _File);

	// ���� ������� FlipBook ������ ������ Sprite �� ���° �ε�������
	fwrite(&m_CurFrmIdx, sizeof(int), 1, _File);
	fwrite(&m_FPS, sizeof(float), 1, _File);
	fwrite(&m_AccTime, sizeof(float), 1, _File);
	fwrite(&m_Repeat, sizeof(bool), 1, _File);
}

void HHFlipbookRenderer::LoadFromFile(FILE* _File)
{
	// FlipBook ���� ��� �ҷ�����
	size_t FlipBookCount = 0;
	fread(&FlipBookCount, sizeof(size_t), 1, _File);
	for (size_t i = 0; i < FlipBookCount; ++i)
	{
		Ptr<HHFlipbook> pFlipBook;
		LoadAssetReference(pFlipBook, _File);
		m_vecFlipbook.push_back(pFlipBook);
	}

	// ���� ������� FlipBook ���� �ε�
	LoadAssetReference(m_CurFlipbook, _File);

	// ���� ������� FlipBook ������ ������ Sprite
	LoadAssetReference(m_CurFrmSprite, _File);

	// ���� ������� FlipBook ������ ������ Sprite �� ���° �ε�������
	fread(&m_CurFrmIdx, sizeof(int), 1, _File);
	fread(&m_FPS, sizeof(float), 1, _File);
	fread(&m_AccTime, sizeof(float), 1, _File);
	fread(&m_Repeat, sizeof(bool), 1, _File);
}
