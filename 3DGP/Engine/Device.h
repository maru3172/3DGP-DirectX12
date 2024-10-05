#pragma once

// �η»繫�� ���� ���̴�
// �޾ƿͼ� �پ��� ȭ���� ����� �����Ѵ�
class Device
{
	// Com (Component Object Model)
	// DX�� ���α׷��� ��� �������� ���� ȣȯ���� �����ϰ� ���ִ� ���
	// COM ��ü(COM�������̽�)�� ���, ���λ����� �츮���� ������
	// ComPtr - ������ ����Ʈ ������
	ComPtr<ID3D12Debug> _debugController;
	ComPtr<IDXGIFactory> _dxgi; // ȭ�� ���� ��ɵ�
	ComPtr<ID3D12Device> _device; // ���� ��ü ����
public:
	void Init();

	ComPtr<IDXGIFactory> GetDXGI() { return _dxgi; }
	ComPtr<ID3D12Device> GetDevice() { return _device; }
};