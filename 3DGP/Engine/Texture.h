#pragma once
#include "Object.h"

class Texture : public Object
{
	ScratchImage			 		_image;
	ComPtr<ID3D12Resource>			_tex2D;

	ComPtr<ID3D12DescriptorHeap>	_srvHeap;
	D3D12_CPU_DESCRIPTOR_HANDLE		_srvHandle = {};
public:
	Texture();
	virtual ~Texture();

	virtual void Load(const std::wstring& path) override;

	D3D12_CPU_DESCRIPTOR_HANDLE GetCpuHandle() { return _srvHandle; }

	void CreateTexture(const std::wstring& path);
	void CreateView();
};

