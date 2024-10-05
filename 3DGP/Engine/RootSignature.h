#pragma once

// 계약서, 결재 단계
// CPU가 사용해야할 부분을 GPU에게 외주를 주고 사용하는 형태였음
// 그러나 둘의 사용 공간은 다르다.
class RootSignature
{
	ComPtr<ID3D12RootSignature> _signature;

public:
	void Init(ComPtr<ID3D12Device> device);

	ComPtr<ID3D12RootSignature> GetSignature() { return _signature; }
};