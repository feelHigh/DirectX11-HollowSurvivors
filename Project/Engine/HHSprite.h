#pragma once
#include "HHAsset.h"

class HHSprite :
    public HHAsset
{
public:
    HHSprite();
    ~HHSprite();

    void Create(Ptr<HHTexture> _Atlas, Vec2 _LeftTopPixel, Vec2 _SlicePixel);

    virtual int Load(const wstring& _FilePath) override;
    virtual int Save(const wstring& _FilePath) override;

    void SetLeftTop(Vec2 _LeftTop);
    void SetSlice(Vec2 _Slice);
    void SetBackground(Vec2 _Background);
    void SetOffset(Vec2 _Offset);

    Ptr<HHTexture> GetAtlasTexture() { return m_Atlas; }
    Vec2 GetLeftTopUV() { return m_LeftTopUV; }
    Vec2 GetSliceUV() { return m_SliceUV; }
    Vec2 GetBackgroundUV() { return m_BackgroundUV; }
    Vec2 GetOffsetUV() { return m_OffsetUV; }

private:
    Ptr<HHTexture>  m_Atlas;
    Vec2            m_LeftTopUV;        // UV ÁÂÇ¥°è
    Vec2            m_SliceUV;          // UV ÁÂÇ¥°è   
    Vec2            m_BackgroundUV;
    Vec2            m_OffsetUV;

};
