#pragma once
class Engine
{
private:
	// �׷��� ȭ�� ũ�� ����
	WindowInfo _window;
	D3D12_VIEWPORT _viewport = { };
	D3D12_RECT _scissorRect = { };

	std::shared_ptr<class Device> _device;
	std::shared_ptr<class CommandQueue> _cmdQueue;
	std::shared_ptr<class SwapChain> _swapChain;
	std::shared_ptr<class DescriptorHeap> _descHeap;
public:
	void Init(const WindowInfo& window);

	void Render();

	void RenderBegin();
	void RenderEnd();

	void ResizeWindow(int32 width, int32 height); // ������ â ũ�� ����
};