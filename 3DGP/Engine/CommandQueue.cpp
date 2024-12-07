#include "pch.h"
#include "CommandQueue.h"
#include "SwapChain.h"
#include "Engine.h"

CommandQueue::~CommandQueue()
{
	// �̺�Ʈ �߻� �� �Ҹ���Ѽ� �����ϰ� ���ư��� ������.
	::CloseHandle(_fenceEvent);
}

void CommandQueue::Init(ComPtr<ID3D12Device> device, std::shared_ptr<SwapChain> swapChain)
{
	_swapChain = swapChain;

	D3D12_COMMAND_QUEUE_DESC queueDesc = { };
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

	// cmdQueue ����
	device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&_cmdQueue));

	// - D3D12_COMMAND_LIST_TYPE_DIRECT : GPU�� ���� �����ϴ� ��� ���
	// �۾� ��� ��ŭ ������ �����
	device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&_cmdAlloc));

	// GPU�� �ϳ��� �ý��ۿ����� 0����
	// DIRECT or BUNDLE
	// Allocator
	// �ʱ� ���� (�׸��� ����� nullptr ����)
	// �ʱ� ���¸� �޾ƿ� ����Ʈ�� ����µ�, Alloc�� ������ ���༭ ���߿� list�� ������ �α׸� �� ���ư���
	// list�� ������ �ٽ� ���� �� �޸𸮴� ���ư����� �뷮�� �ٽ� ������ ��(c++ capacity ���� ������).
	device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, _cmdAlloc.Get(), nullptr, IID_PPV_ARGS(&_cmdList));

	// CommandList�� Close / Open ���°� �ִµ�
	// Open ���¿��� Command�� �ִٰ� Close�� ���� �����ϴ� ����
	// �ҷ����°� ��û �ϱ� �� �ݰ� �����ؼ� �����ϴ� ����
	_cmdList->Close();

	device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&_resCmdAlloc));
	device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, _resCmdAlloc.Get(), nullptr, IID_PPV_ARGS(&_resCmdList));

	// CreateFence
	// - CPU�� GPU�� ����ȭ �������� ���δ�
	// ��Ÿ���� �������
	device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&_Fence));
	_fenceEvent = ::CreateEvent(nullptr, FALSE, FALSE, nullptr);
	// �̰� ��ȣ�� ���� �ǵ� ó������ �����ٰ� Ư�� ������ �����Ǹ� ������ �����ϴ� �׷� ����.
}

// ���� ���� ���� �� ���� ���� �� ����
// ������ �׷��� GPU�� ����Ǵ� ���� CPU�� ��� �ų� �ٸ� ����
void CommandQueue::WaitSync()
{
	// fence ����� 0���� 1�� ������Ű�� �� ������ ��ȣ�� �ű�
	_fenceValue++;

	// Ŀ�ǵ� ť�� ��ȣ�� �ѱ��
	_cmdQueue->Signal(_Fence.Get(), _fenceValue);

	if (_Fence->GetCompletedValue() < _fenceValue)
	{
		//GPU�� Fence�� �� ��ȣ�� �̺�Ʈ���� �������� fenceEvent�� �����Ŵ.
		_Fence->SetEventOnCompletion(_fenceValue, _fenceEvent);

		// ���� Fence�� ������ ������ ������ ��ٸ��� �ݺ�
		::WaitForSingleObject(_fenceEvent, INFINITE);
	}
}

void CommandQueue::RenderBegin(const D3D12_VIEWPORT* vp, const D3D12_RECT* rect)
{
	_cmdAlloc->Reset();
	_cmdList->Reset(_cmdAlloc.Get(), nullptr);

	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		_swapChain->GetBackRTVBuffer().Get(),
		D3D12_RESOURCE_STATE_PRESENT, // ȭ�� ���
		D3D12_RESOURCE_STATE_RENDER_TARGET); // ���� �����

	// ��Ʈ �ñ״�ó ���� Ȱ��
	_cmdList->SetGraphicsRootSignature(ROOT_SIGNATURE.Get());

	GEngine->GetConstantBuffer(CONSTANT_BUFFER_TYPE::TRANSFORM)->Clear();
	GEngine->GetConstantBuffer(CONSTANT_BUFFER_TYPE::MATERIAL)->Clear();

	GEngine->GetTableDescHeap()->Clear();

	// �����ͼ� ������ DescriptorHeap
	ID3D12DescriptorHeap* descHeap = GEngine->GetTableDescHeap()->GetDescriptorHeap().Get();
	_cmdList->SetDescriptorHeaps(1, &descHeap);

	_cmdList->ResourceBarrier(1, &barrier);
	
	// Ŀ�ǵ� ����Ʈ�� �а� �踮� �򸮸� ������ �ٽ� �������
	_cmdList->RSSetViewports(1, vp);
	_cmdList->RSSetScissorRects(1, rect);

	// � ���ۿ��ٰ� �׸��� �׷��� ���� �ٽ� �ѹ� ����� ����, descHeap���� BackBuffer�� �ҷ��ͼ� �� ������� gpu���� �׷��޶� ��û
	D3D12_CPU_DESCRIPTOR_HANDLE backBufferView = _swapChain->GetBackRTV();
	_cmdList->ClearRenderTargetView(backBufferView, Colors::Black, 0, nullptr);

	D3D12_CPU_DESCRIPTOR_HANDLE depthStencilView = GEngine->GetDepthStencilBuffer()->GetDSVCpuHandle();
	_cmdList->OMSetRenderTargets(1, &backBufferView, FALSE, &depthStencilView);

	_cmdList->ClearDepthStencilView(depthStencilView, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void CommandQueue::RenderEnd()
{
	// �̹��� �ٲ�ġ��
	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		_swapChain->GetBackRTVBuffer().Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, // ���� �����
		D3D12_RESOURCE_STATE_PRESENT); // ȭ�� ���

	_cmdList->ResourceBarrier(1, &barrier);
	_cmdList->Close(); // ������ �ݾƳ���

	// Ŀ�ǵ� ����Ʈ ����
	ID3D12CommandList* cmdListArr[] = { _cmdList.Get() };
	_cmdQueue->ExecuteCommandLists(_countof(cmdListArr), cmdListArr);  // �����ض�

	_swapChain->Present(); // ���۸� �̿��� ȭ���� ä���
	
	// �� �Ϸ��� ������ ���� ���� ������ cpu�� ������
	WaitSync();

	// ���� ����� �ε����� �ٲ�ġ�� �������ν� ������ �غ� ��ġ��
	_swapChain->SwapIndex();
}

void CommandQueue::FlushResourceCommandQueue()
{
	_resCmdList->Close();

	// �潺 ���� ����
	ID3D12CommandList* cmdListArr[] = { _resCmdList.Get() };
	_cmdQueue->ExecuteCommandLists(_countof(cmdListArr), cmdListArr);

	// ��ũ ��
	WaitSync();

	// ����, �ٽ� ����� �غ� ������
	_resCmdAlloc->Reset();
	_resCmdList->Reset(_resCmdAlloc.Get(), nullptr);
}