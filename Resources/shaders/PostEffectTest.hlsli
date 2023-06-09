cbuffer cbuff0  : register(b0)
{
    float time;
    bool start;
};

// 頂点シェーダーからピクセルシェーダーへのやり取りに使用する構造体
struct VSOutput
{
    float4 svpos : SV_POSITION;
    float2 uv : TEXCOORD0;
};
