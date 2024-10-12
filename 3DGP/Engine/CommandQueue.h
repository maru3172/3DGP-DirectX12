#pragma once

// 현재 클래스에서 타 클래스 타입을 가져오고 싶을때 2가지 방법이 있음
// 하나는 이렇게 전역변수 라인에 선언을 해서 전방선언을 하는거고
// 또 하나는 저 아래에 타입을넣을 때 <class 클래스이름> 이렇게 붙여서 가져오는 방식임
class SwapChain;
class DescriptorHeap;

class CommandQueue
{
	// CommandQueue : DX12에 등장
	// 외주를 요청할 때, 하나씩 요청하면 비효율적
	// [외주 목록]에 일감을 차곡차곡 기록했다가 한 방에 요청하는 것
	// 즉 받아놓은 의뢰를 모아놨다가 한 방에 보내주는 기능임
	ComPtr<ID3D12CommandQueue> _cmdQueue; // 넣고 한 번에 보내줌
	ComPtr<ID3D12CommandAllocator> _cmdAlloc; // 그런 넣는 공간을 할당해주는 기능
	ComPtr<ID3D12GraphicsCommandList> _cmdList; // 일감을 리스트화 함

	// Fence : 울타리(?) - CPU가 GPU 작업할 때 갑자기 들어와서 작업하면 안됨
	// 그러므로 CPU는 GPU가 작업이 끝날 때까지 동작하지 않게 장막같은걸 치게 만드는데
	// 그게 바로 동기화임 -> 그러한 기능을 해주는 친구
	// CPU / GPU 동기화를 위한 간단한 도구
	ComPtr<ID3D12Fence> _Fence;
	uint32 _fenceValue = 0;
	HANDLE _fenceEvent = INVALID_HANDLE_VALUE;

	std::shared_ptr<SwapChain> _swapChain;
public:

	~CommandQueue(); // 소멸자

	void Init(ComPtr<ID3D12Device> device, std::shared_ptr<SwapChain> swapChain);
	void WaitSync(); // Fence 이용, 다 끝날 때까지 기다려라.

	void RenderBegin(const D3D12_VIEWPORT* vp, const D3D12_RECT* rect);
	void RenderEnd();

	ComPtr<ID3D12CommandQueue> GetCmdQueue() { return _cmdQueue; }
	ComPtr<ID3D12GraphicsCommandList> GetCmdList() { return _cmdList; }
};

