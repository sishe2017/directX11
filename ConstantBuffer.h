#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <vector>
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4x4.h"


//DirectX11�ĳ���������
class ConstantBuffer
{
	friend class VertexShader;
	friend class PixelShader;

public:
	ConstantBuffer(float val);
	ConstantBuffer(Vector2 vector2);
	ConstantBuffer(Vector3 vector3);
	ConstantBuffer(Matrix4x4 matrix);
	ConstantBuffer(std::vector<float> arr);

private:
	//�����Ļ�����
	Microsoft::WRL::ComPtr<ID3D11Buffer> pBuffer;
};
