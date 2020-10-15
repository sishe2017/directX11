#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <vector>
#include "../Geometry/Vector2.h"
#include "../Geometry/Vector3.h"
#include "../Geometry/Matrix4x4.h"


//DirectX11的常量缓冲区
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
	//常量的缓冲区
	Microsoft::WRL::ComPtr<ID3D11Buffer> pBuffer;
};
