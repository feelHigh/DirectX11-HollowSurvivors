#include "SpriteEditorSub.h"

class SpriteEditorDetail :
    public SpriteEditorSub
{
public:
    SpriteEditorDetail();
    ~SpriteEditorDetail();

    virtual void Initialize() override;
    virtual void Update() override;

    void SetAtlasTex(Ptr<HHTexture> _Tex);

private:
    Ptr<HHTexture>   m_AtlasTex;

    void Atlas();
    void AtlasInfo();

    void SelectTexture(DWORD_PTR _ListUI);
};
