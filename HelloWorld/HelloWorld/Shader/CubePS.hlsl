//纹理
Texture2D texture0 : register(t0);
//采样器
SamplerState sampler0 : register(s0);


float4 main(float2 texCrd : TEXCOORD) : SV_TARGET
{
    //根据纹理坐标对纹理进行采样
    return texture0.Sample(sampler0, texCrd);
}