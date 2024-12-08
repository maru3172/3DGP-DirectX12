#pragma once

// ��༭, ���� �ܰ�
// CPU�� ����ؾ��� �κ��� GPU���� ���ָ� �ְ� ����ϴ� ���¿���
// �׷��� ���� ��� ������ �ٸ���.
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