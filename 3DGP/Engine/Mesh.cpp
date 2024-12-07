#include "pch.h"
#include "Mesh.h"
#include "Engine.h"
#include "Material.h"

Mesh::Mesh() : Object(OBJECT_TYPE::MESH)
{

}

Mesh::~Mesh()
{

}

// 인덱스 삼각형 리스트로 변경
void Mesh::Init(const std::vector<Vertex>& vertexBuffer, const std::vector<uint32>& indexBuffer)
{
	CreateVertexBuffer(vertexBuffer);
	CreateIndexBuffer(indexBuffer);
}

void Mesh::Render()
{
	// 이제 그릴 시간
	CMD_LIST->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 정점의 형태와 어떻게 연결되어 있지?
	CMD_LIST->IASetVertexBuffers(0, 1, &_vertexBufferView); // Slot: (0~15)
	CMD_LIST->IASetIndexBuffer(&_indexBufferView); // 인덱스 버퍼 보면서 삼각형 그리기

	GEngine->GetTableDescHeap()->CommitTable();

	// CMD_LIST->DrawInstanced(_vertexCount, 1, 0, 0);
	CMD_LIST->DrawIndexedInstanced(_indexCount, 1, 0, 0, 0); // 인덱스를 가져와 그려주세요
}

// 버텍스(점)를 생성하고 데이터 넣기
void Mesh::CreateVertexBuffer(const std::vector<Vertex>& buffer)
{
	_vertexCount = static_cast<uint32>(buffer.size());
	uint32 bufferSize = _vertexCount * sizeof(Vertex);

	D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

	DEVICE->CreateCommittedResource(
		&heapProperty,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&_vertexBuffer));

	// 삼각형 정점 데이터를 정점 버퍼에 복사
	// Copy the triangle data to the vertex buffer.
	void* vertexDataBuffer = nullptr;
	CD3DX12_RANGE readRange(0, 0); // We do not intend to read from this resource on the CPU.
	_vertexBuffer->Map(0, &readRange, &vertexDataBuffer);
	::memcpy(vertexDataBuffer, &buffer[0], bufferSize);
	_vertexBuffer->Unmap(0, nullptr);

	// Initialize the vertex buffer view. 정점 버퍼 초기화 부분
	_vertexBufferView.BufferLocation = _vertexBuffer->GetGPUVirtualAddress();
	_vertexBufferView.StrideInBytes = sizeof(Vertex); // 정점 1개 크기
	_vertexBufferView.SizeInBytes = bufferSize; // 버퍼의 크기	
}

// 버텍스를 가져와 인덱스 리스트 생성
void Mesh::CreateIndexBuffer(const std::vector<uint32>& buffer)
{
	_indexCount = static_cast<uint32>(buffer.size());
	uint32 bufferSize = _indexCount * sizeof(uint32);

	D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

	DEVICE->CreateCommittedResource(
		&heapProperty,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&_indexBuffer));

	void* indexDataBuffer = nullptr;
	CD3DX12_RANGE readRange(0, 0); // We do not intend to read from this resource on the CPU.
	_indexBuffer->Map(0, &readRange, &indexDataBuffer);
	::memcpy(indexDataBuffer, &buffer[0], bufferSize);
	_indexBuffer->Unmap(0, nullptr);
	// 여기까진 정점 버퍼를 가져와 그걸 기반으로 인덱스 버퍼가 만들어진다.

	// 버텍스 버퍼랑 동일하지 않은 부분은 여기 - 인덱스 크기 및 지정
	_indexBufferView.BufferLocation = _indexBuffer->GetGPUVirtualAddress();
	_indexBufferView.Format = DXGI_FORMAT_R32_UINT;
	_indexBufferView.SizeInBytes = bufferSize;
}