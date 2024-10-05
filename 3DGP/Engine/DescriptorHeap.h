#pragma once

// [기안서]
// 외주를 맡길 때 이런 저런 정보들을 같이 넘겨줘야 하는데,
// 아무 형태로나 요청하면 못 알아먹는다
// - 각종 리소스를 어떤 용도로 사용하는지 꼼꼼하게 적어서 넘겨주는 용도
// 양식에 맞춰서 넌 이렇게 이런 용도로 사용해야돼를 알려주는 것
// 그냥 건내주면 지 맘대로 쓰니까 그렇게 안하게 방지
class DescriptorHeap // 또 다른 말로는 View라고도 함
	
{
	ComPtr<ID3D12DescriptorHeap> _rtvHeap;
	uint32 _rtvHeapSize = 0;
	D3D12_CPU_DESCRIPTOR_HANDLE _rtvHandle[SWAP_CHAIN_BUFFER_COUNT];

	std::shared_ptr<class SwapChain> _swapChain;
public:
	void Init(ComPtr<ID3D12Device> device, std::shared_ptr<class SwapChain> swapChain);

	D3D12_CPU_DESCRIPTOR_HANDLE GetRTV(int32 idx) { return _rtvHandle[idx]; } // 랜덤 타겟 뷰를 불러오는 핸들

	D3D12_CPU_DESCRIPTOR_HANDLE GetBackBufferView(); //현재 스왑 체인에서 백 버퍼 인덱스를 참고해 그 RTV를 꺼내옴
};