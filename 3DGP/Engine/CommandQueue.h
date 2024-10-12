#pragma once

// ���� Ŭ�������� Ÿ Ŭ���� Ÿ���� �������� ������ 2���� ����� ����
// �ϳ��� �̷��� �������� ���ο� ������ �ؼ� ���漱���� �ϴ°Ű�
// �� �ϳ��� �� �Ʒ��� Ÿ�������� �� <class Ŭ�����̸�> �̷��� �ٿ��� �������� �����
class SwapChain;
class DescriptorHeap;

class CommandQueue
{
	// CommandQueue : DX12�� ����
	// ���ָ� ��û�� ��, �ϳ��� ��û�ϸ� ��ȿ����
	// [���� ���]�� �ϰ��� �������� ����ߴٰ� �� �濡 ��û�ϴ� ��
	// �� �޾Ƴ��� �Ƿڸ� ��Ƴ��ٰ� �� �濡 �����ִ� �����
	ComPtr<ID3D12CommandQueue> _cmdQueue; // �ְ� �� ���� ������
	ComPtr<ID3D12CommandAllocator> _cmdAlloc; // �׷� �ִ� ������ �Ҵ����ִ� ���
	ComPtr<ID3D12GraphicsCommandList> _cmdList; // �ϰ��� ����Ʈȭ ��

	// Fence : ��Ÿ��(?) - CPU�� GPU �۾��� �� ���ڱ� ���ͼ� �۾��ϸ� �ȵ�
	// �׷��Ƿ� CPU�� GPU�� �۾��� ���� ������ �������� �ʰ� �帷������ ġ�� ����µ�
	// �װ� �ٷ� ����ȭ�� -> �׷��� ����� ���ִ� ģ��
	// CPU / GPU ����ȭ�� ���� ������ ����
	ComPtr<ID3D12Fence> _Fence;
	uint32 _fenceValue = 0;
	HANDLE _fenceEvent = INVALID_HANDLE_VALUE;

	std::shared_ptr<SwapChain> _swapChain;
public:

	~CommandQueue(); // �Ҹ���

	void Init(ComPtr<ID3D12Device> device, std::shared_ptr<SwapChain> swapChain);
	void WaitSync(); // Fence �̿�, �� ���� ������ ��ٷ���.

	void RenderBegin(const D3D12_VIEWPORT* vp, const D3D12_RECT* rect);
	void RenderEnd();

	ComPtr<ID3D12CommandQueue> GetCmdQueue() { return _cmdQueue; }
	ComPtr<ID3D12GraphicsCommandList> GetCmdList() { return _cmdList; }
};

