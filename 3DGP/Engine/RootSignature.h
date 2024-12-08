#pragma once

// 계약서, 결재 단계
// CPU가 사용해야할 부분을 GPU에게 외주를 주고 사용하는 형태였음
// 그러나 둘의 사용 공간은 다르다.
class RootSignature
{
	D3D12_STATIC_SAMPLER_DESC _samplerDesc;
	ComPtr<ID3D12RootSignature> _graphicsRootSignature;
	ComPtr<ID3D12RootSignature> _computeRootSignature;

	void CreateGraphicsRootSignature();
	void CreateComputeRootSignature();
public:
	void Init();

	ComPtr<ID3D12RootSignature> GetGraphicsRootSignature() { return _graphicsRootSignature; }
	ComPtr<ID3D12RootSignature> GetComputeRootSignature() { return _computeRootSignature; }
};