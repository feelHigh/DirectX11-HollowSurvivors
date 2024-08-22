#pragma once
#include "EditorUI.h"

class SpriteEditorAtlasView;
class SpriteEditorDetail;

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

private:
    SpriteEditorAtlasView* m_AtlasView;
    SpriteEditorDetail* m_Detail;

};
