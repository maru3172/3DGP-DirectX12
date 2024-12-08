#pragma once

// ��ȯ �罽 - ���� ���۸� ��Ȯ�� �ǹ�
	// [���� ����]
	// - ���� ���� ���� �ִ� ��Ȳ�� ����
	// - � �������� ��� ������� ������
	// - GPU�� ������ ��� (����)
	// - ����� �޾Ƽ� ȭ�鿡 �׷��ش�

	// [���� �����]�� ��� ����?
	// - � ����(Buffer)�� �׷��� �ǳ��޶�� ��Ź�غ���
	// - Ư�� ���̸� ���� -> ó���� �ǳ��ְ� -> ������� �ش� ���̿� �޴´� OK
	// - �츮 ȭ�鿡 Ư�� ����(���� �����) ������ش�

	// [?]
	// - �׷��� ȭ�鿡 ���� ����� ����ϴ� ���߿�, ���� ȭ�鵵 ���ָ� �ðܾ� ��
	// - ���� ȭ�� ������� �̹� ȭ�� ��¿� �����
	// - Ư�� ���̸� 2�� ����, �ϳ��� ���� ȭ���� �׷��ְ�, �ϳ��� ���� �ñ��...
	// ���粬 ���� ������ ���� ����� �ٷ� ���� �ðܼ� �׸��� �ϰ� �װ� ����
	// �� ���� �ߴ��� �ٽ� ���� �ñ�� �ݺ��ϸ� �� ������ �������� ������ �� �� ����
	// - Double Buffering!

	// - [0] [1]
	// ���� ȭ�� [1]  <-> GPU �۾��� [1] BackBuffer

class SwapChain
{
	ComPtr<IDXGISwapChain> _swapChain;
	
	uint32 _backBufferIndex = 0; // �ڿ��� �۾����� ���� �ε���
	void CreateSwapChain(const WindowInfo& info, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue);
public:
	void Init(const WindowInfo& info, ComPtr<ID3D12Device> device, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue);
	void Present();
	void SwapIndex();

	ComPtr<IDXGISwapChain> GetSwapChain() { return _swapChain; }
	uint8 GetBackBufferIndex() { return _backBufferIndex;  }
};