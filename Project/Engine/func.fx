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
    
    // DirectionalLight �� ���
    if (0 == Info.Type)
    {
        _Light.Ambient.rgb += Info.LightEssence.Ambient.rgb;
    }
    
    // PointLight �� ���
    else if (1 == Info.Type)
    {
         // �������� �ȼ������� �Ÿ�
        /*
        float fDist = distance(Info.WorldPosition.xy, _WorldPosition.xy);
        
        // �Ÿ����� ������ ġȯ�ؼ� �Ÿ��� ���� ���� ���⸦ �ڻ��� �׷��� ���·� ����Ѵ�.
        float fPow = saturate(cos((fDist / Info.Radius) * (PI / 2.f)));
        
        // �������κ��� ������ �Ÿ��� ���� ���� ����
        //float fPow2 = saturate(1.f - fDist / Info.Radius);
        
        // ���� ���� ��� = ���� �� * �Ÿ������� ����
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
    
    // SpotLight �� ���
    else
    {
        float fAttenu = 1.f;

        float fDist = distance(Info.WorldPosition.xy, _WorldPosition.xy);
        float2 toPoint = normalize(Info.WorldPosition.xy - _WorldPosition.xy); // ������ġ-> ������ġ�� ���ϴ� ���⺤��
        float cosTheta = dot(normalize(Info.WorldDirection.xy), toPoint); // ���� ���ϴ� ����� ���� �޴� �������� ���Ͱ��� ����
        
        if (fDist < Info.Radius)
        {
            // cosTheta > info.fAngle / 2.f : ���� �ȼ��� �߻��ϴ� ���� ���� ���� ���� ����
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