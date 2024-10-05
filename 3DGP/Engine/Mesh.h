#pragma once

// �޽� - �������� �̷���� ��ü, ������ ����
class Mesh
{
	ComPtr<ID3D12Resource> _vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW _vertexBufferView = { };
	uint32 _vertexCount = 0;
public:
	void Init(std::vector<Vertex>& vec);
	void Render();
};