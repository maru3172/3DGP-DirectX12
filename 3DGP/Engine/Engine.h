#pragma once
#include "Device.h"
#include "CommandQueue.h"
#include "SwapChain.h"
#include "RootSignature.h"
#include "Mesh.h"
#include "Shader.h"
#include "ConstantBuffer.h"
#include "TableDescriptorHeap.h"
#include "Texture.h"
#include "DepthStencilBuffer.h"

#include "Input.h"
#include "Timer.h"

class Engine
{
	// 그려질 화면 크기 관련
	WindowInfo _window;
	D3D12_VIEWPORT _viewport = { };
	D3D12_RECT _scissorRect = { };

	// 각 클래스의 정보들을 가져오기
	std::shared_ptr<Device> _device = std::make_shared<Device>();
	std::shared_ptr<CommandQueue> _cmdQueue = std::make_shared<CommandQueue>();
	std::shared_ptr<SwapChain> _swapChain = std::make_shared<SwapChain>();
	std::shared_ptr<RootSignature> _rootSignature = std::make_shared<RootSignature>();
	std::shared_ptr<ConstantBuffer> _cb = std::make_shared<ConstantBuffer>();
	std::shared_ptr<TableDescriptorHeap> _tableDescHeap = std::make_shared<TableDescriptorHeap>();
	std::shared_ptr<DepthStencilBuffer> _depthStencilBuffer = std::make_shared<DepthStencilBuffer>();

	std::shared_ptr<Input> _input = std::make_shared<Input>();
	std::shared_ptr<Timer> _timer = std::make_shared<Timer>();

	void ShowFps();
public:
	std::shared_ptr<Device> GetDevice() { return _device; }
	std::shared_ptr<CommandQueue> GetCmdQueue() { return _cmdQueue; }
	std::shared_ptr<SwapChain> GetSwapChain() { return _swapChain; }
	std::shared_ptr<RootSignature> GetRootSignature() { return _rootSignature; }
	std::shared_ptr<ConstantBuffer> GetCB() { return _cb; }
	std::shared_ptr<TableDescriptorHeap> GetTableDescHeap() { return _tableDescHeap; }
	std::shared_ptr<DepthStencilBuffer> GetDepthStencilBuffer() { return _depthStencilBuffer; }

	std::shared_ptr<Input> GetInput() { return _input; }
	std::shared_ptr<Timer> GetTimer() { return _timer; }

	void Init(const WindowInfo& window);

	void Render();

	void Update();

	void RenderBegin();
	void RenderEnd();

	void ResizeWindow(int32 width, int32 height); // 윈도우 창 크기 변경
};