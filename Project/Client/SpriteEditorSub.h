#pragma once
#include "EditorUI.h"

#include "SpriteEditor.h"
#include <Engine/HHAssetMgr.h>

class SpriteEditorSub :
    public EditorUI
{
public:
    SpriteEditorSub();
    ~SpriteEditorSub();

    friend class SpriteEditor;

    SpriteEditor* GetOwner() { return m_Owner; }
    class SpriteEditorDetail* GetDetail() { return m_Owner->GetDetail(); }
    class SpriteEditorAtlasView* GetAtlasView() { return m_Owner->GetAtlasView(); }
    class SpriteEditorFlipbookPreview* GetPreview() { return m_Owner->GetPreview(); }

private:
    SpriteEditor* m_Owner;

};
