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

private:


};
