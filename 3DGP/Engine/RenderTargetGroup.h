#pragma once
#include "Texture.h"

enum class RENDER_TARGET_GROUP_TYPE : uint8
{
	SWAP_CHAIN, // BACK_BUFFER, FRONT_BUFFER
	G_BUFFER, // POSITION, NORMAL, COLOR
	END,
};

enum
{
	RENDER_TARGET_G_BUFFER_GROUP_MEMBER_COUNT = 3,
	RENDER_TARGET_GROUP_COUNT = static_cast<uint8>(RENDER_TARGET_GROUP_TYPE::END)
};

struct RenderTarget
{
	std::shared_ptr<Texture> target;
	float clearColor[4];
};

class RenderTargetGroup
{
	RENDER_TARGET_GROUP_TYPE _groupType;
	std::vector<RenderTarget> _rtVec;
	uint32 _rtCount;
	std::shared_ptr<Texture> _dsTexture;
	ComPtr<ID3D12DescriptorHeap> _rtvHeap;
	uint32 _rtvHeapSize;
	D3D12_CPU_DESCRIPTOR_HANDLE _rtvHeapBegin;
	D3D12_CPU_DESCRIPTOR_HANDLE _dsvHeapBegin;
public:
	void Create(RENDER_TARGET_GROUP_TYPE groupType, std::vector<RenderTarget>& rtVec, std::shared_ptr<Texture> dsTexture);

	void OMSetRenderTargets(uint32 count, uint32 offset);
	void OMSetRenderTargets();

	void ClearRenderTargetView(uint32 index);
	void ClearRenderTargetView();

	std::shared_ptr<Texture> GetRTTexture(uint32 index) { return _rtVec[index].target; }
	std::shared_ptr<Texture> GetDSTexture() { return _dsTexture; }
};