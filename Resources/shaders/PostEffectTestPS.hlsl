#include "PostEffectTest.hlsli"

Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);

float4 main(VSOutput input) : SV_TARGET
{
    float2 samplePoint = input.uv;
    float4 texcolor = tex.Sample(smp, input.uv);
    float timeFactor = time * 0.2;  // 時間の係数を調整することで演出の進行速度を制御

    float sinv = sin(input.uv);  // sin関数に時間係数を乗算
    float steped = step(0.99, sinv * sinv);
    float vignette = length(float2(0.5, 0.6) - input.uv);

    float effectStrength = timeFactor * 0.5;  // 演出の強さを時間係数に応じて調整
    float effect1 = abs(sin(input.uv.y * 50.0 + timeFactor * 2.0)) * 0.05;
    float effect2 = abs(sin(input.uv.y * 100.0 - timeFactor * 4.0)) * 0.08;

    // 演出を徐々に適用
    float3 finalColor = texcolor.rgb;
    if (start)
    {
        if (time < 7)
        {
            finalColor -= (1 - steped) * effect1 * effectStrength;
            finalColor -= (1 - steped) * effect2 * effectStrength;
            finalColor -= vignette * effectStrength / 5;
            finalColor += steped * 0.1;
        }
        else
        {
            finalColor -= (1 - steped) * effect1;
            finalColor -= (1 - steped) * effect2;
            vignette = clamp(vignette - 0.2, 0.1, 1);
            finalColor -= vignette * effectStrength / 5;
        }
    }
    

    return float4(finalColor, texcolor.a);
}