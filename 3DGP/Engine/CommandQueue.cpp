#include "pch.h"
#include "CommandQueue.h"
#include "SwapChain.h"
#include "DescriptorHeap.h"

CommandQueue::~CommandQueue()
{
	// 이벤트 발생 후 소멸시켜서 원만하게 돌아가게 해주자.
	::CloseHandle(_fenceEvent);
}

void CommandQueue::Init(ComPtr<ID3D12Device> device, std::shared_ptr<SwapChain> swapChain, std::shared_ptr<DescriptorHeap> descHeap)
{
	_swapChain = swapChain;
	_descHeap = descHeap;

	D3D12_COMMAND_QUEUE_DESC queueDesc = { };
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

	// cmdQueue 생성
	device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&_cmdQueue));

	// - D3D12_COMMAND_LIST_TYPE_DIRECT : GPU가 직접 실행하는 명령 목록
	// 작업 목록 만큼 공간을 만들고
	device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&_cmdAlloc));

	// GPU가 하나인 시스템에서는 0으로
	// DIRECT or BUNDLE
	// Allocator
	// 초기 상태 (그리기 명령은 nullptr 지정)
	// 초기 상태를 받아와 리스트를 만드는데, Alloc이 관리를 해줘서 나중에 list의 내용이 싸그리 다 날아가고
	// list의 내용을 다시 받을 때 메모리는 날아가지만 용량은 다시 유지가 됨(c++ capacity 같은 느낌임).
	device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, _cmdAlloc.Get(), nullptr, IID_PPV_ARGS(&_cmdList));

	// CommandList는 Close / Open 상태가 있는데
	// Open 상태에서 Command를 넣다가 Close한 다음 제출하는 개념
	// 불러오는걸 요청 하기 전 닫고 마감해서 제출하는 느낌
	_cmdList->Close();

	// CreateFence
	// - CPU와 GPU의 동기화 수단으로 쓰인다
	// 울타리를 만들어줌
	device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&_Fence));
	_fenceEvent = ::CreateEvent(nullptr, FALSE, FALSE, nullptr);
	// 이건 신호등 같은 건데 처음에는 꺼졌다가 특정 조건이 만족되면 켜져서 수행하는 그런 거임.
}

// 딱히 좋다 느낄 수 없다 느낄 수 있음
// 이유가 그런게 GPU가 실행되는 동안 CPU는 노는 거나 다름 없음
void CommandQueue::WaitSync()
{
	// fence 밸류를 0부터 1씩 증가시키며 그 상태의 번호를 매김
	_fenceValue++;

	// 커맨드 큐에 번호를 넘기고
	_cmdQueue->Signal(_Fence.Get(), _fenceValue);

	if (_Fence->GetCompletedValue() < _fenceValue)
	{
		//GPU가 Fence에 그 번호의 이벤트까지 끝났으면 fenceEvent를 실행시킴.
		_Fence->SetEventOnCompletion(_fenceValue, _fenceEvent);

		// 다음 Fence에 도달할 때까지 무한정 기다리며 반복
		::WaitForSingleObject(_fenceEvent, INFINITE);
	}
}

void CommandQueue::RenderBegin(const D3D12_VIEWPORT* vp, const D3D12_RECT* rect)
{
	_cmdAlloc->Reset();
	_cmdList->Reset(_cmdAlloc.Get(), nullptr);

	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		_swapChain->GetCurrentBackBufferResource().Get(),
		D3D12_RESOURCE_STATE_PRESENT, // 화면 출력
		D3D12_RESOURCE_STATE_RENDER_TARGET); // 외주 결과물

	_cmdList->ResourceBarrier(1, &barrier);
	
	// 커맨드 리스트를 밀고 배리어가 깔리면 세팅을 다시 해줘야함
	_cmdList->RSSetViewports(1, vp);
	_cmdList->RSSetScissorRects(1, rect);

	// 어떤 버퍼에다가 그림을 그려야 할지 다시 한번 언급을 해줌, descHeap에서 BackBuffer를 불러와서 그 대상으로 gpu에게 그려달라 요청
	D3D12_CPU_DESCRIPTOR_HANDLE backBufferView = _descHeap->GetBackBufferView();
	_cmdList->ClearRenderTargetView(backBufferView, Colors::LightSteelBlue, 0, nullptr);
	_cmdList->OMSetRenderTargets(1, &backBufferView, FALSE, nullptr);
}

void CommandQueue::RenderEnd()
{
	// 이번엔 바꿔치기
	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		_swapChain->GetCurrentBackBufferResource().Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, // 외주 결과물
		D3D12_RESOURCE_STATE_PRESENT); // 화면 출력

	_cmdList->ResourceBarrier(1, &barrier);
	_cmdList->Close(); // 끝내면 닫아놓자

	// 커맨드 리스트 수행
	ID3D12CommandList* cmdListArr[] = { _cmdList.Get() };
	_cmdQueue->ExecuteCommandLists(_countof(cmdListArr), cmdListArr);  // 실행해라

	_swapChain->Present(); // 버퍼를 이용해 화면을 채우고
	
	// 이 일련의 과정이 전부 끝낼 때까지 cpu는 대기상태
	WaitSync();

	// 기존 백버퍼 인덱스를 바꿔치기 해줌으로써 스왑할 준비를 마치자
	_swapChain->SwapIndex();
}