#pragma once
#include "ComponentUI.h"

class CameraUI :
    public ComponentUI
{
public:
    CameraUI();
    ~CameraUI();

private:
    bool m_ShowLayerCheck;

    virtual void Update() override;

    void LayerCheck();
    void Projection();

};
