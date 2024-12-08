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
#include "RenderTargetGroup.h"

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
	std::shared_ptr<TableDescriptorHeap> _tableDescHeap = std::make_shared<TableDescriptorHeap>();

	std::vector<std::shared_ptr<ConstantBuffer>> _constantBuffers;
	std::array<std::shared_ptr<RenderTargetGroup>, RENDER_TARGET_GROUP_COUNT> _rtGroups;

	void ShowFps();
	void CreateConstantBuffer(CBV_REGISTER reg, uint32 bufferSize, uint32 count);
	void CreateRenderTargetGroups();
public:
	const WindowInfo& GetWindow() { return _window; }
	std::shared_ptr<Device> GetDevice() { return _device; }
	std::shared_ptr<CommandQueue> GetCmdQueue() { return _cmdQueue; }
	std::shared_ptr<SwapChain> GetSwapChain() { return _swapChain; }
	std::shared_ptr<RootSignature> GetRootSignature() { return _rootSignature; }
	std::shared_ptr<TableDescriptorHeap> GetTableDescHeap() { return _tableDescHeap; }

	std::shared_ptr<ConstantBuffer> GetConstantBuffer(CONSTANT_BUFFER_TYPE type) { return _constantBuffers[static_cast<uint8>(type)]; }
	std::shared_ptr<RenderTargetGroup> GetRTGroup(RENDER_TARGET_GROUP_TYPE type) { return _rtGroups[static_cast<uint8>(type)]; }

	void Init(const WindowInfo& window);
	void Update();

	void Render();
	void RenderBegin();
	void RenderEnd();

	void ResizeWindow(int32 width, int32 height); // 윈도우 창 크기 변경
};