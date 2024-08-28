#ifndef _STD2D
#define _STD2D

#include "value.fx"
#include "func.fx"

// Vertex Shader
struct VTX_IN
{
    float3 vPosition : POSITION;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};

struct VTX_OUT
{
    float4 vPosition : SV_Position;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
    
    float3 vWorldPosition : POSITION;
};

VTX_OUT VS_Standard(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;
    
    output.vPosition = mul(float4(_in.vPosition, 1.f), matWVP);
    
    output.vColor = _in.vColor;
    
    output.vUV = _in.vUV;
    
    output.vWorldPosition = mul(float4(_in.vPosition, 1.f), matWorld).xyz;
    
    return output;
}

float4 PS_Standard(VTX_OUT _in) : SV_Target
{
    float4 vColor = float4(0.f, 0.f, 0.f, 1.f);
    
    if (UseFlipbook)
    {            
        float2 BackGroundLeftTop = LeftTopUV - (BackGroundUV - SliceUV) / 2.f;
        float2 vSpriteUV = BackGroundLeftTop + (_in.vUV * BackGroundUV);
        vSpriteUV -= OffsetUV;
                
        if (LeftTopUV.x <= vSpriteUV.x && vSpriteUV.x <= LeftTopUV.x + SliceUV.x
            && LeftTopUV.y <= vSpriteUV.y && vSpriteUV.y <= LeftTopUV.y + SliceUV.y)
        {
            vColor = g_AtlasTex.Sample(g_sam_1, vSpriteUV);
        }
        else
        {
            discard;
        }
    }
    else
    {        
        if (g_btex_0)
        {
            vColor = g_tex_0.Sample(g_sam_1, _in.vUV);
        }
        else
        {
            vColor = float4(1.f, 0.f, 1.f, 1.f);
        }
    }
    
    if (vColor.a == 0.f)
    {
        discard;
    }
    
    // ±¤¿ø Àû¿ë      
    tLight Light = (tLight) 0.f;
    
    for (int i = 0; i < g_Light2DCount; ++i)
    {
        CalculateLight2D(i, _in.vWorldPosition, Light);
    }
    
    vColor.rgb = vColor.rgb * Light.Color.rgb 
               + vColor.rgb * Light.Ambient.rgb;
    
    
    return vColor;
}

#endif