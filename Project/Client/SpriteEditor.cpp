#include "pch.h"
#include "SpriteEditor.h"

#include "HHEditorMgr.h"
#include "SpriteEditorAtlasView.h"
#include "SpriteEditorDetail.h"
#include "SpriteEditorFlipbookPreview.h"

SpriteEditor::SpriteEditor()
	: m_AtlasView(nullptr)
	, m_Detail(nullptr)
	, m_Preview(nullptr)
{
	UseMenuBar(true);
}

SpriteEditor::~SpriteEditor()
{
}

void SpriteEditor::Initialize()
{
	m_AtlasView = (SpriteEditorAtlasView*)HHEditorMgr::GetInstance()->FindEditorUI("SpriteEditorAtlasView");
	m_Detail = (SpriteEditorDetail*)HHEditorMgr::GetInstance()->FindEditorUI("SpriteEditorDetail");
	m_Preview = (SpriteEditorFlipbookPreview*)HHEditorMgr::GetInstance()->FindEditorUI("SpriteEditorFlipbookPreview");

	m_AtlasView->m_Owner = this;
	m_Detail->m_Owner = this;
	m_Preview->m_Owner = this;

	m_Detail->SetAtlasTex(HHAssetMgr::GetInstance()->Load<HHTexture>(L"Texture2D\\Player\\PlayerSpritesheet-alpha.png"
																	, L"Texture2D\\Player\\PlayerSpritesheet-alpha.png"));
}

void SpriteEditor::Update()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Window"))
		{
			bool AtlasView = m_AtlasView->IsActive();
			bool Detail = m_Detail->IsActive();

			if (ImGui::MenuItem("AtlasView", nullptr, &AtlasView))
			{
				m_AtlasView->SetActive(AtlasView);
			}

			if (ImGui::MenuItem("Detail", nullptr, &Detail))
			{
				m_Detail->SetActive(Detail);
			}

			if (ImGui::MenuItem("Flipbook Preview", nullptr, &m_Preview))
			{
				m_Preview->SetActive(m_Preview);
			}

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}
}

void SpriteEditor::Activate()
{
	m_AtlasView->SetActive(true);
	m_Detail->SetActive(true);
	m_Preview->SetActive(true);
}

void SpriteEditor::Deactivate()
{
	m_AtlasView->SetActive(false);
	m_Detail->SetActive(false);
	m_Preview->SetActive(false);
}
