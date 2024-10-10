#pragma once

// 메쉬 - 정점으로 이루어진 물체, 정점의 모임
class Mesh
{
	ComPtr<ID3D12Resource> _vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW _vertexBufferView = { };
	uint32 _vertexCount = 0;

	Transform _transform = {};
public:
	void Init(std::vector<Vertex>& vec);
	void Render();

	void SetTransform(const Transform& t) { _transform = t; }
};