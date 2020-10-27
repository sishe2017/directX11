
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

VSOut main(float3 pos : POSITION, float2 texCrd : TEXCOORD)
{
    VSOut vsOut;
    vsOut.pos = mul(float4(pos, 1.0f), transform);
    vsOut.texCrd = texCrd;
    return vsOut;
}