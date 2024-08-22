#ifndef _FUNC
#define _FUNC

#include "value.fx"
#include "struct.fx"

int IsBinding(Texture2D _tex)
{
    int width = 0, height = 0;
    _tex.GetDimensions(width, height);
    
    if (0 == width || height == 0)
        return false;
    
    return true;
}

void CalculateLight2D(int _LightIdx, float3 _WorldPosition, inout tLight _Light)
{
    tLightInfo Info = g_Light2D[_LightIdx];
    
    // DirectionalLight 인 경우
    if (0 == Info.Type)
    {
        _Light.Ambient.rgb += Info.LightEssence.Ambient.rgb;
    }
    
    // PointLight 인 경우
    else if (1 == Info.Type)
    {
         // 점광원과 픽셀까지의 거리
        /*
        float fDist = distance(Info.WorldPosition.xy, _WorldPosition.xy);
        
        // 거리값을 각도로 치환해서 거리에 따른 빛의 세기를 코사인 그래프 형태로 사용한다.
        float fPow = saturate(cos((fDist / Info.Radius) * (PI / 2.f)));
        
        // 광원으로부터 떨어진 거리에 따른 빛의 세기
        //float fPow2 = saturate(1.f - fDist / Info.Radius);
        
        // 최종 색상 계산 = 빛의 색 * 거리에따른 세기
        _Light.Color.rgb += Info.LightInfo.Color.rgb * fPow;
        _Light.Ambient.rgb += Info.LightInfo.Ambient.rgb;
        */
        float fAttenu = 1.f;
        
        float fDist = distance(Info.WorldPosition.xy, _WorldPosition.xy);
        if (fDist < Info.Radius)
        {
            if (g_int_0)
            {
                float fTheta = (fDist / Info.Radius) * (PI / 2.f);
                fAttenu = saturate(cos(fTheta));
            }
            else
            {
                fAttenu = saturate(1.f - fDist / g_Light2D[0].Radius);
            }
            
            _Light.Color += Info.LightEssence.Color * fAttenu;
        }
    }
    
    // SpotLight 인 경우
    else
    {
        float fAttenu = 1.f;

        float fDist = distance(Info.WorldPosition.xy, _WorldPosition.xy);
        float2 toPoint = normalize(Info.WorldPosition.xy - _WorldPosition.xy); // 현재위치-> 광원위치로 향하는 방향벡터
        float cosTheta = dot(normalize(Info.WorldDirection.xy), toPoint); // 빛이 향하는 방향과 빛을 받는 지점까지 벡터간의 각도
        
        if (fDist < Info.Radius)
        {
            // cosTheta > info.fAngle / 2.f : 현재 픽셀이 발산하는 빛의 각도 범위 내에 있음
            if (cosTheta > cos(radians(Info.Angle) / 2.f))
            {
                float fTheta = (fDist / Info.Radius) * (PI / 2.f);
                fAttenu = saturate(cos(fTheta));
            
                _Light.Color += Info.LightEssence.Color * fAttenu;
            }
        }
    }
}

float3 GetRandom(in Texture2D _NoiseTexture, uint _ID, uint _maxId)
{
    float2 vUV = (float2) 0.f;
    vUV.x = ((float) _ID / (float) (_maxId - 1)) + g_EngineTime * 0.5f;
    vUV.y = sin(vUV.x * 20 * PI) * 0.5f + g_EngineTime * 0.1f;
    float3 vRandom = _NoiseTexture.SampleLevel(g_sam_1, vUV, 0).xyz;
    
    return vRandom;
}

#endif