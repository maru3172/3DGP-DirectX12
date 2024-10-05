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
	ComPtr<ID3D12Resource> _renderTargets[SWAP_CHAIN_BUFFER_COUNT]; // ���� �׸� ���
	uint32 _backBufferIndex = 0; // �ڿ��� �۾����� ���� �ε���
public:
	void Init(const WindowInfo& info, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue);
	void Present();
	void SwapIndex();

	ComPtr<IDXGISwapChain> GetSwapChain() { return _swapChain; }
	ComPtr<ID3D12Resource> GetRenderTarget(int32 index) { return _renderTargets[index]; } // ���ҽ� �ޱ�

	uint32 GetCurretBackBufferIndex() { return _backBufferIndex; }
	ComPtr<ID3D12Resource> GetCurrentBackBufferResource() { return _renderTargets[_backBufferIndex]; } // �۾��� ���ҽ� �ޱ�
};