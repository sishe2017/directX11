//����
Texture2D texture0 : register(t0);
//������
SamplerState sampler0 : register(s0);


float4 main(float2 texCrd : TEXCOORD) : SV_TARGET
{
    //�������������������в���
    return texture0.Sample(sampler0, texCrd);
}