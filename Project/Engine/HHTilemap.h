#pragma once
#include "HHRenderComponent.h"

class HHStructuredBuffer;

struct tTileInfo
{
    int ImgIdx;
    int padding[3];
};

class HHTilemap :
    public HHRenderComponent
{
public:
    CLONE(HHTilemap);
    HHTilemap();
    HHTilemap(const HHTilemap& _Origin);
    ~HHTilemap();

    virtual void Begin() override;
    virtual void FinalTick() override;
    virtual void Render() override;

    void SetRowCol(int _Row, int _Col);
    void SetTileSize(Vec2 _Size);
    void SetAtlasTexture(Ptr<HHTexture> _Atlas);
    void SetAtlasTileSize(Vec2 _TileSize);

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

private:
    int                     m_Row;              // TileMap �� �� ����
    int                     m_Col;              // TileMap �� �� ����
    Vec2                    m_TileSize;         // Tile 1���� ũ��

    Ptr<HHTexture>          m_TileAtlas;        // Tile ���� �̹������� �����ϰ� �ִ� ��Ʋ�� �ؽ���
    Vec2                    m_AtlasResolution;  // Atlas �ؽ��� �ػ�
    Vec2                    m_AtlasTileSize;    // Atlas �ؽ��� ������ Ÿ�� 1���� ũ��
    Vec2                    m_AtlasTileSliceUV; // Atlas �ؽ��� ������ Ÿ�� 1���� ũ�⸦ UV �� ��ȯ�� ũ��(SliceUV)

    int                     m_AtlasMaxRow;      // Atlas �ؽ��İ� �����ϰ� �ִ� Ÿ���� �ִ� �� ����
    int                     m_AtlasMaxCol;      // Atlas �ؽ��İ� �����ϰ� �ִ� Ÿ���� �ִ� �� ����

    vector<tTileInfo>       m_vecTileInfo;      // ������ Ÿ���� ����
    HHStructuredBuffer*     m_Buffer;           // // ������ Ÿ�������� t �������ͷ� �����ϱ� ���� ����ȭ����

    void ChangeTilemapSize();

};
