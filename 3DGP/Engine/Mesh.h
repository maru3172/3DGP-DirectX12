#pragma once

// 메쉬 - 정점으로 이루어진 물체, 정점의 모임
class Mesh
{
	ComPtr<ID3D12Resource> _vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW _vertexBufferView = { };
	uint32 _vertexCount = 0;

	ComPtr<ID3D12Resource>		_indexBuffer;
	D3D12_INDEX_BUFFER_VIEW		_indexBufferView;
	uint32 _indexCount = 0;

	Transform _transform = {};

	void CreateVertexBuffer(const std::vector<Vertex>& buffer);
	void CreateIndexBuffer(const std::vector<uint32>& buffer);
public:
	void Init(const std::vector<Vertex>& vertexBuffer, const std::vector<uint32>& indexBuffer);
	void Render();

	void SetTransform(const Transform& t) { _transform = t; }
};