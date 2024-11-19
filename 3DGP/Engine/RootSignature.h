#pragma once

// ��༭, ���� �ܰ�
// CPU�� ����ؾ��� �κ��� GPU���� ���ָ� �ְ� ����ϴ� ���¿���
// �׷��� ���� ��� ������ �ٸ���.
class RootSignature
{
	ComPtr<ID3D12RootSignature> _signature;
	D3D12_STATIC_SAMPLER_DESC _samplerDesc;

	void CreateSamplerDesc();

	void CreateRootSignature();
public:
	void Init();

	ComPtr<ID3D12RootSignature> GetSignature() { return _signature; }
};