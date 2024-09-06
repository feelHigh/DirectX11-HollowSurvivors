#pragma once
#include "SpriteEditorSub.h"

class SpriteEditorAtlasView :
    public SpriteEditorSub
{
public:
    SpriteEditorAtlasView();
    ~SpriteEditorAtlasView();

    virtual void Initialize() override;
    virtual void Update() override;

    void SetAtlasTex(Ptr<HHTexture> _Tex);

    const vector<Ptr<HHSprite>>& GetSelectedSprites() const { return m_SelectedSprites; }

private:
    Ptr<HHTexture>  m_AtlasTex;

    float           m_WidthSize;
    float           m_WheelScale;
    float           m_Ratio;        // ���� �ػ� ��� ��� �̹����� ����

    ImVec2          ImageRectMin;   // Image ���� �»�� ���� ��ġ

    ImVec2          m_MousePos;     // ���� ���콺 ��ġ

    ImVec2          m_MouseLT;      // ���콺 ��ġ�� �ش��ϴ� Texture �� �ȼ� ��ǥ
    ImVec2          m_MouseRB;      // ���콺 ��ġ�� �ش��ϴ� Texture �� �ȼ� ��ǥ
    set<Vec2>       m_PixelID;      // ��ϵ����� �ִ� �ȼ����� Ȯ���ϴ� �뵵

    vector<Ptr<HHSprite>> m_SelectedSprites;

    void WheelCheck();
    void SelectCheck();
    void DrawSelectRect();
    void CalculateSpriteSize(Vec2 _PixelPos);
    bool IsValidPixel(Vec2 _PixelPos);

};
