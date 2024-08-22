#pragma once
#include "singleton.h"

class HHCamera;
class HHGameObject;
class HHLight2D;
class HHStructuredBuffer;

class HHRenderMgr :
    public HHSingleton<HHRenderMgr>
{
    SINGLE(HHRenderMgr);

public:
    void Initialize();
    void Tick();

    void RegisterCamera(HHCamera* _Cam, int _CamPriority);
    void RegisterEditorCamera(HHCamera* _Cam) { m_EditorCamera = _Cam; }
    void AddDebugShapeInfo(const tDebugShapeInfo& _Info) { m_DebugShapeList.push_back(_Info); }
    void RegisterLight2D(HHLight2D* _Light) { m_vecLight2D.push_back(_Light); }

    void PostProcessCopy();

private:
    vector<HHCamera*>       m_vecCam;
    HHCamera*               m_EditorCamera;

    HHGameObject*           m_DebugObject;
    list<tDebugShapeInfo>   m_DebugShapeList;

    // Light
    vector<HHLight2D*>      m_vecLight2D;
    HHStructuredBuffer*     m_Light2DBuffer;

    // PostProcess
    Ptr<HHTexture>          m_PostProcessTex;

    void RenderStart();
    void RenderDebugShape();
    void Clear();

};
