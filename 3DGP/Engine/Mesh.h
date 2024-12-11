#pragma once
#include "Object.h"

class Material;

struct IndexBufferInfo
{
	ComPtr<ID3D12Resource>		buffer;
	D3D12_INDEX_BUFFER_VIEW		bufferView;
	DXGI_FORMAT					format;
	uint32						count;
};

// 메쉬 - 정점으로 이루어진 물체, 정점의 모임
class Mesh : public Object
{
	ComPtr<ID3D12Resource> _vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW _vertexBufferView = {};
	uint32 _vertexCount = 0;

	std::vector<IndexBufferInfo>		_vecIndexInfo;

	void CreateVertexBuffer(const std::vector<Vertex>& buffer);
	void CreateIndexBuffer(const std::vector<uint32>& buffer);
public:
	Mesh();
	virtual ~Mesh();

	void Create(const std::vector<Vertex>& vertexBuffer, const std::vector<uint32>& indexBuffer);
	void Render(uint32 instanceCount = 1, uint32 idx = 0);
	void Render(std::shared_ptr<class InstancingBuffer>& buffer, uint32 idx = 0);

	static std::shared_ptr<Mesh> CreateFromFBX(const struct FbxMeshInfo* meshInfo);

	uint32 GetSubsetCount() { return static_cast<uint32>(_vecIndexInfo.size()); }
};