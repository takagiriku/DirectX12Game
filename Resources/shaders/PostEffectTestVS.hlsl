#include "PostEffectTest.hlsli"

VSOutput main(float4 pos : POSITION, float2 uv : TEXCOORD0)
{
    VSOutput output;
    output.svpos = pos;
    output.uv = uv;

    return output;
}
