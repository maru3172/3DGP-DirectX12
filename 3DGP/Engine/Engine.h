#pragma once
#include "Device.h"
#include "CommandQueue.h"
#include "SwapChain.h"
#include "RootSignature.h"
#include "Mesh.h"
#include "Shader.h"
#include "ConstantBuffer.h"
#include "TableDescriptorHeap.h"

class Engine
{
private:
	// 그려질 화면 크기 관련
	WindowInfo _window;
	D3D12_VIEWPORT _viewport = { };
	D3D12_RECT _scissorRect = { };

	std::shared_ptr<Device> _device;
	std::shared_ptr<CommandQueue> _cmdQueue;
	std::shared_ptr<SwapChain> _swapChain;
	std::shared_ptr<RootSignature> _rootSignature;
	std::shared_ptr<ConstantBuffer> _cb;
	std::shared_ptr<TableDescriptorHeap> _tableDescHeap;
public:
	std::shared_ptr<Device> GetDevice() { return _device; }
	std::shared_ptr<CommandQueue> GetCmdQueue() { return _cmdQueue; }
	std::shared_ptr<SwapChain> GetSwapChain() { return _swapChain; }
	std::shared_ptr<RootSignature> GetRootSignature() { return _rootSignature; }
	std::shared_ptr<ConstantBuffer> GetCB() { return _cb; }
	std::shared_ptr<TableDescriptorHeap> GetTableDescHeap() { return _tableDescHeap; }

	void Init(const WindowInfo& window);

	void Render();

	void RenderBegin();
	void RenderEnd();

	void ResizeWindow(int32 width, int32 height); // 윈도우 창 크기 변경
};