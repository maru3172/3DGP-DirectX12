#pragma once

// [��ȼ�]
// ���ָ� �ñ� �� �̷� ���� �������� ���� �Ѱ���� �ϴµ�,
// �ƹ� ���·γ� ��û�ϸ� �� �˾ƸԴ´�
// - ���� ���ҽ��� � �뵵�� ����ϴ��� �Ĳ��ϰ� ��� �Ѱ��ִ� �뵵
// ��Ŀ� ���缭 �� �̷��� �̷� �뵵�� ����ؾߵŸ� �˷��ִ� ��
// �׳� �ǳ��ָ� �� ����� ���ϱ� �׷��� ���ϰ� ����
class DescriptorHeap // �� �ٸ� ���δ� View��� ��
	
{
	ComPtr<ID3D12DescriptorHeap> _rtvHeap;
	uint32 _rtvHeapSize = 0;
	D3D12_CPU_DESCRIPTOR_HANDLE _rtvHandle[SWAP_CHAIN_BUFFER_COUNT];

	std::shared_ptr<class SwapChain> _swapChain;
public:
	void Init(ComPtr<ID3D12Device> device, std::shared_ptr<class SwapChain> swapChain);

	D3D12_CPU_DESCRIPTOR_HANDLE GetRTV(int32 idx) { return _rtvHandle[idx]; } // ���� Ÿ�� �並 �ҷ����� �ڵ�

	D3D12_CPU_DESCRIPTOR_HANDLE GetBackBufferView(); //���� ���� ü�ο��� �� ���� �ε����� ������ �� RTV�� ������
};