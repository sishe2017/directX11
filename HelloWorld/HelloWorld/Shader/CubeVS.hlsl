
//常量缓存
cbuffer transform
{
    matrix transform;
};

//顶点着色器的输出
struct VSOut
{
    //纹理坐标
    float2 texCrd : TEXCOORD;
    //顶点位置
    float4 pos : SV_Position;
};

float4 main(float3 pos : POSITION, float2 texCrd : TEXCOORD) : SV_POSITION
{
    VSOut vsOut;
    vsOut.pos = mul(float4(pos, 1.0f), transform);
    vsOut.texCrd = texCrd;
    return vsOut;
}