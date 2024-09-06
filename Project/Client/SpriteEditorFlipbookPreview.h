#pragma once
#include "SpriteEditorSub.h"

class SpriteEditorFlipbookPreview :
    public SpriteEditorSub
{
public:
    SpriteEditorFlipbookPreview();
    ~SpriteEditorFlipbookPreview();

    virtual void Initialize() override;
    virtual void Update() override;

    void SetSpritesToPreview(const vector<Ptr<HHSprite>>& sprites);
    void SaveFlipbook(const wstring& filePath);

private:
    vector<Ptr<HHSprite>> m_TemporarySprites; // Temporary preview values
    float m_TemporaryFPS = 30.0f; // Default FPS

    void RenderPreview();
    void HighlightFrame(Ptr<HHSprite> sprite);
};
