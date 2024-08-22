#ifndef _POSTPROCESS
#define POSTPROCESS

#include "value.fx"

// ==========================
// GrayFilterShader
// Mesh     : RectMesh
// DSTYPE   : NO_TEST_NO_WRITE
// g_tex_0  : TargetCopyTex
// g_tex_1  : NoiseTexture 1
// g_tex_2  : NoiseTexture 2
// g_tex_3  : NoiseTexture 3
// ===========================
struct VS_IN
{
    float3 vPosition    : POSITION;
    float2 vUV          : TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition    : SV_Position;
    float2 vUV          : TEXCOORD;
};

VS_OUT VS_GrayFilter(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    // Proj 행렬을 곱한 결과는 각 xyz 에 자신의 ViewZ 가 곱혀져있는 형태이다.
    // W 자리에 자신의 ViewZ 가 출력되기 때문에 이것으로 각 xyz 를 나누어야 실제 Proj 좌표가 나온다.
    // 따라서 Rasterizer State 에 투영행렬을 곱한 결과를 전달하면 각 xyz 를 w 로 나누어서 사용한다.
    output.vPosition = float4(_in.vPosition.xy * 2.f, 0.f, 1.f);
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_GrayFilter(VS_OUT _in) : SV_Target
{
    // GrayFilter
    float4 vColor = g_tex_0.Sample(g_sam_0, _in.vUV);    
    float Average = (vColor.x + vColor.y + vColor.z) / 3.f;
    vColor = float4(Average, Average, Average, 1.f); 
        
    // Cos Distortion
    //float2 vUV = _in.vUV;    
    //vUV.y += cos( (vUV.x + g_EngineTime * 0.1f) * PI * 12.f) * 0.01;    
    //float4 vColor = g_tex_0.Sample(g_sam_0, vUV);
    
    // Noise
    //float2 vUV = _in.vUV;
    //vUV.x += g_EngineTime * 0.1;
    
    //float4 vNoise = g_tex_3.Sample(g_sam_0, vUV);
    //vNoise = (vNoise * 2.f - 1.f) * 0.01f;
    //vUV = _in.vUV + vNoise.xy;
    
    //float4 vColor = g_tex_0.Sample(g_sam_0, vUV);
    //vColor.b *= 1.5f;
    
    return vColor;
}

// ==========================
// Distortion Shader
// Mesh     : RectMesh
// DSTYPE   : NO_TEST_NO_WRITE
// g_tex_0  : TargetCopyTex
// g_tex_1  : NoiseTexture 1
// g_tex_2  : NoiseTexture 2
// g_tex_3  : NoiseTexture 3
// ===========================
VS_OUT VS_Distortion(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = mul(float4(_in.vPosition, 1.f), matWVP);
    output.vUV = _in.vUV;
    
    return output;
}


float4 PS_Distortion(VS_OUT _in) : SV_Target
{
    // 1. 렌더타겟 해상도 정보 (전역 상수버퍼)    
    // 2. 픽셀쉐이더의 픽셀 좌표
    float2 vScreenUV = _in.vPosition.xy / g_Resolution;
    
    float2 vNoiseUV = vScreenUV;
    vNoiseUV.x += g_EngineTime * 0.1;
    float4 vNoise = g_tex_3.Sample(g_sam_0, vNoiseUV);
    
    vNoise = (vNoise * 2.f - 1.f) * 0.01f;
    vScreenUV = vScreenUV + vNoise.xy;
    float4 vColor = g_tex_0.Sample(g_sam_0, vScreenUV);
    
    return vColor;
}

// ==========================
// SepiaTone Shader
// Mesh     : RectMesh
// DSTYPE   : NO_TEST_NO_WRITE
// g_tex_0  : TargetCopyTex
// ===========================
VS_OUT VS_SepiaTone(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = float4(_in.vPosition.xy * 2.f, 0.f, 1.f);
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_SepiaTone(VS_OUT _in) : SV_Target
{
    float4 vColor = g_tex_0.Sample(g_sam_0, _in.vUV);
    
    float4 sepiaColor;
    sepiaColor.r = dot(vColor.rgb, float3(0.393, 0.769, 0.189));
    sepiaColor.g = dot(vColor.rgb, float3(0.349, 0.686, 0.168));
    sepiaColor.b = dot(vColor.rgb, float3(0.272, 0.534, 0.131));
    sepiaColor.a = vColor.a;
    
    return sepiaColor;
}

// ==========================
// InvertColor Shader
// Mesh     : RectMesh
// DSTYPE   : NO_TEST_NO_WRITE
// g_tex_0  : TargetCopyTex
// ===========================
VS_OUT VS_InvertColor(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = float4(_in.vPosition.xy * 2.f, 0.f, 1.f);
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_InvertColor(VS_OUT _in) : SV_Target
{
    float4 vColor = g_tex_0.Sample(g_sam_0, _in.vUV);
    vColor.rgb = 1.0 - vColor.rgb; // Invert colors
    
    return vColor;
}

// ==========================
// Blur Shader
// Mesh     : RectMesh
// DSTYPE   : NO_TEST_NO_WRITE
// g_tex_0  : TargetCopyTex
// ===========================
VS_OUT VS_Blur(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = float4(_in.vPosition.xy * 2.f, 0.f, 1.f);
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_Blur(VS_OUT _in) : SV_Target
{
    float4 vColor = float4(0.0, 0.0, 0.0, 0.0);
    
    // Simple box blur
    float2 texOffset = 1.0 / g_Resolution; // Texture coordinate offset for sampling
    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            vColor += g_tex_0.Sample(g_sam_0, _in.vUV + float2(x, y) * texOffset);
        }
    }
    vColor /= 9.0; // Average the sampled colors
    
    return vColor;
}

// ==========================
// Bloom Shader
// Mesh     : RectMesh
// DSTYPE   : NO_TEST_NO_WRITE
// g_tex_0  : TargetCopyTex
// ===========================
VS_OUT VS_Bloom(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = float4(_in.vPosition.xy * 2.f, 0.f, 1.f);
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_Bloom(VS_OUT _in) : SV_Target
{
    float4 vColor = float4(0.0, 0.0, 0.0, 0.0);
    
    // Extract bright areas
    float4 brightColor = g_tex_0.Sample(g_sam_0, _in.vUV);
    float brightness = dot(brightColor.rgb, float3(0.299, 0.587, 0.114));
    if (brightness > 0.8)
    {
        vColor = brightColor;
    }

    // Blur bright areas
    float2 texOffset = 1.0 / g_Resolution;
    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            vColor += g_tex_0.Sample(g_sam_0, _in.vUV + float2(x, y) * texOffset) * 0.25;
        }
    }
    
    return vColor;
}
#endif