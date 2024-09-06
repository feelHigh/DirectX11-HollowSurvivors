#pragma once
#include "EditorUI.h"

class SpriteEditorAtlasView;
class SpriteEditorDetail;
class SpriteEditorFlipbookPreview;

class SpriteEditor :
    public EditorUI
{
public:
    SpriteEditor();
    ~SpriteEditor();

    virtual void Initialize() override;
    virtual void Update() override;

    virtual void Activate() override;
    virtual void Deactivate() override;

    SpriteEditorAtlasView* GetAtlasView() { return m_AtlasView; }
    SpriteEditorDetail* GetDetail() { return m_Detail; }
    SpriteEditorFlipbookPreview* GetPreview() { return m_Preview; }

private:
    SpriteEditorAtlasView* m_AtlasView;
    SpriteEditorDetail* m_Detail;
    SpriteEditorFlipbookPreview* m_Preview;

};
