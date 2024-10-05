#pragma once

// ��༭, ���� �ܰ�
// CPU�� ����ؾ��� �κ��� GPU���� ���ָ� �ְ� ����ϴ� ���¿���
// �׷��� ���� ��� ������ �ٸ���.
class RootSignature
{
	ComPtr<ID3D12RootSignature> _signature;

public:
	void Init(ComPtr<ID3D12Device> device);

	ComPtr<ID3D12RootSignature> GetSignature() { return _signature; }
};