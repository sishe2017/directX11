
//��������
cbuffer transform
{
    matrix transform;
};

//������ɫ�������
struct VSOut
{
    //��������
    float2 texCrd : TEXCOORD;
    //����λ��
    float4 pos : SV_Position;
};

float4 main(float3 pos : POSITION, float2 texCrd : TEXCOORD) : SV_POSITION
{
    VSOut vsOut;
    vsOut.pos = mul(float4(pos, 1.0f), transform);
    vsOut.texCrd = texCrd;
    return vsOut;
}