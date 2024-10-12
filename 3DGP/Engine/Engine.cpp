#include "pch.h"
#include "Engine.h"


void Engine::Init(const WindowInfo& window)
{
	_window = window;
	ResizeWindow(_window.width, _window.height);

	// �׷��� ȭ�� ũ�� ����
	_viewport = { 0,0,static_cast<FLOAT>(window.width), static_cast<FLOAT>(window.height), 0.0f, 1.0f };
	_scissorRect = CD3DX12_RECT(0, 0, window.width, window.height);

	// �� Ŭ������ �������� ��������
	_device = std::make_shared<Device>();
	_cmdQueue = std::make_shared<CommandQueue>();
	_swapChain = std::make_shared<SwapChain>();
	_rootSignature = std::make_shared<RootSignature>();
	_cb = std::make_shared<ConstantBuffer>();
	_tableDescHeap = std::make_shared<TableDescriptorHeap>();

	_device->Init();
	_cmdQueue->Init(_device->GetDevice(), _swapChain);
	_swapChain->Init(window, _device->GetDevice(), _device->GetDXGI(), _cmdQueue->GetCmdQueue());
	_rootSignature->Init(_device->GetDevice());
	_cb->Init(sizeof(Transform), 256);
	_tableDescHeap->Init(512);
}

void Engine::Render()
{
	RenderBegin();

	//������ ��ü �׸�

	RenderEnd();
}

void Engine::RenderBegin()
{
	_cmdQueue->RenderBegin(&_viewport, &_scissorRect);
}

void Engine::RenderEnd()
{
	_cmdQueue->RenderEnd();
}

void Engine::ResizeWindow(int32 width, int32 height) // ������ â ũ�� ����
{
	_window.width = width;
	_window.height = height;
	RECT rect = { 0, 0, width, height };
	::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	::SetWindowPos(_window.hWnd, 0, 100, 100, width, height, 0);
}