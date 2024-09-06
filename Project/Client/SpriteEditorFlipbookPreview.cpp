#include "pch.h"
#include "SpriteEditorFlipbookPreview.h"

#include <Engine/HHSprite.h>
#include <Engine/HHFlipbook.h>
#include <Engine/HHFlipbookRenderer.h>

SpriteEditorFlipbookPreview::SpriteEditorFlipbookPreview()
{
}

SpriteEditorFlipbookPreview::~SpriteEditorFlipbookPreview()
{
}

void SpriteEditorFlipbookPreview::Initialize()
{
}

void SpriteEditorFlipbookPreview::Update()
{
    // Render preview based on temporary values
    //RenderPreview();

    // Allow user to change FPS using ImGui
    ImGui::SliderFloat("FPS", &m_TemporaryFPS, 1.0f, 120.0f);
}

void SpriteEditorFlipbookPreview::SetSpritesToPreview(const vector<Ptr<HHSprite>>& sprites)
{
    // Store the selected sprites for preview
    //m_TemporarySprites = sprites;
}

void SpriteEditorFlipbookPreview::RenderPreview()
{
    /*static int currentFrame = 0;
    static float elapsedTime = 0.0f;

    elapsedTime += ImGui::GetIO().DeltaTime;

    if (elapsedTime >= (1.0f / m_TemporaryFPS)) 
    {
        currentFrame = (currentFrame + 1) % m_TemporarySprites.size();
        elapsedTime = 0.0f;
    }

    for (int i = 0; i < m_TemporarySprites.size(); ++i) 
    {
        RenderSprite(m_TemporarySprites[i]);

        if (i == currentFrame) 
        {
            HighlightFrame(m_TemporarySprites[i]);
        }
    }*/
}

void SpriteEditorFlipbookPreview::HighlightFrame(Ptr<HHSprite> sprite)
{
    //ImVec2 spritePosition = ImGui::GetCursorScreenPos();  // Get position of sprite in the editor window
    //ImVec2 spriteSize = ImVec2(sprite->GetWidth(), sprite->GetHeight());  // Assuming you have GetWidth()/GetHeight() methods

    //// Draws an orange rectangle
    //ImGui::GetWindowDrawList()->AddRect(spritePosition, ImVec2(spritePosition.x + spriteSize.x, spritePosition.y + spriteSize.y),
    //                                    ImGui::GetColorU32(ImVec4(1.f, 0.5f, 0.f, 1.f)), 0.0f, 0, 2.0f);
}

void SpriteEditorFlipbookPreview::SaveFlipbook(const wstring& filePath)
{
    /*Ptr<HHFlipbook> SaveFlipbook = new HHFlipbook();

    for (auto& sprite : m_TemporarySprites)
    {
        SaveFlipbook->AddSprite(sprite);
    }

    SaveFlipbook->Save(filePath);*/
}