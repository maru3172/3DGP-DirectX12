#pragma once
#include "Object.h"

class Texture;
class Material;

// �޽� - �������� �̷���� ��ü, ������ ����
class Mesh : public Object
{
	ComPtr<ID3D12Resource> _vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW _vertexBufferView = { };
	uint32 _vertexCount = 0;

	ComPtr<ID3D12Resource>		_indexBuffer;
	D3D12_INDEX_BUFFER_VIEW		_indexBufferView;
	uint32 _indexCount = 0;

	void CreateVertexBuffer(const std::vector<Vertex>& buffer);
	void CreateIndexBuffer(const std::vector<uint32>& buffer);
public:
	Mesh();
	virtual ~Mesh();

	void Init(const std::vector<Vertex>& vertexBuffer, const std::vector<uint32>& indexBuffer);
	void Render(uint32 instanceCount = 1);
};