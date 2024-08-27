#include "pch.h"
#include "SpriteEditor.h"

#include "HHEditorMgr.h"
#include "SpriteEditorAtlasView.h"
#include "SpriteEditorDetail.h"

SpriteEditor::SpriteEditor()
	: m_AtlasView(nullptr)
	, m_Detail(nullptr)
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

	//m_AtlasView->SetMove(false);
	//m_Detail->SetMove(false);

	m_AtlasView->m_Owner = this;
	m_Detail->m_Owner = this;

	m_Detail->SetAtlasTex(HHAssetMgr::GetInstance()->Load<HHTexture>(L"Texture2D\\Player\\PlayerSpritesheet.png"
																	, L"Texture2D\\Player\\PlayerSpritesheet.png"));
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

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}
}

void SpriteEditor::Activate()
{
	m_AtlasView->SetActive(true);
	m_Detail->SetActive(true);
}

void SpriteEditor::Deactivate()
{
	m_AtlasView->SetActive(false);
	m_Detail->SetActive(false);
}
