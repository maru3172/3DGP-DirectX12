#pragma once
#include "Object.h"

class Texture : public Object
{
	ScratchImage			 		_image;
	ComPtr<ID3D12Resource>			_tex2D;

	ComPtr<ID3D12DescriptorHeap>	_srvHeap;
	ComPtr<ID3D12DescriptorHeap>	_rtvHeap;
	ComPtr<ID3D12DescriptorHeap>	_dsvHeap;

	D3D12_CPU_DESCRIPTOR_HANDLE		_srvHeapBegin = {};
public:
	Texture();
	virtual ~Texture();

	virtual void Load(const std::wstring& path) override;

	void Create(DXGI_FORMAT format, uint32 width, uint32 height,
		const D3D12_HEAP_PROPERTIES& heapProperty, D3D12_HEAP_FLAGS heapFlags,
		D3D12_RESOURCE_FLAGS resFlags, Vec4 clearColor = Vec4());

	void CreateFromResource(ComPtr<ID3D12Resource> tex2D);

	ComPtr<ID3D12Resource> GetTex2D() { return _tex2D; }
	ComPtr<ID3D12DescriptorHeap> GetSRV() { return _srvHeap; }
	ComPtr<ID3D12DescriptorHeap> GetRTV() { return _rtvHeap; }
	ComPtr<ID3D12DescriptorHeap> GetDSV() { return _dsvHeap; }

	D3D12_CPU_DESCRIPTOR_HANDLE GetSRVHandle() { return _srvHeapBegin; }
};