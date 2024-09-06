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
    float           m_Ratio;        // 실제 해상도 대비 출력 이미지의 비율

    ImVec2          ImageRectMin;   // Image 위젯 좌상단 실제 위치

    ImVec2          m_MousePos;     // 실제 마우스 위치

    ImVec2          m_MouseLT;      // 마우스 위치에 해당하는 Texture 의 픽셀 좌표
    ImVec2          m_MouseRB;      // 마우스 위치에 해당하는 Texture 의 픽셀 좌표
    set<Vec2>       m_PixelID;      // 등록된적이 있는 픽셀인지 확인하는 용도

    vector<Ptr<HHSprite>> m_SelectedSprites;

    void WheelCheck();
    void SelectCheck();
    void DrawSelectRect();
    void CalculateSpriteSize(Vec2 _PixelPos);
    bool IsValidPixel(Vec2 _PixelPos);

};
