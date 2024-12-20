#pragma once
#include "Object.h"

class Material;
class StructuredBuffer;

struct IndexBufferInfo
{
	ComPtr<ID3D12Resource>		buffer;
	D3D12_INDEX_BUFFER_VIEW		bufferView;
	DXGI_FORMAT					format;
	uint32						count;
};

struct KeyFrameInfo
{
	double	time;
	int32	frame;
	Vec3	scale;
	Vec4	rotation;
	Vec3	translate;
};

struct BoneInfo
{
	std::wstring					boneName;
	int32					parentIdx;
	Matrix					matOffset;
};

struct AnimClipInfo
{
	std::wstring			animName;
	int32			frameCount;
	double			duration;
	std::vector<std::vector<KeyFrameInfo>>	keyFrames;
};

// 메쉬 - 정점으로 이루어진 물체, 정점의 모임
class Mesh : public Object
{
	ComPtr<ID3D12Resource> _vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW _vertexBufferView = {};
	uint32 _vertexCount = 0;

	std::vector<IndexBufferInfo>		_vecIndexInfo;

	// Animation
	std::vector<AnimClipInfo>			_animClips;
	std::vector<BoneInfo>				_bones;

	std::shared_ptr<StructuredBuffer>	_offsetBuffer; // 각 뼈의 offset 행렬
	std::vector<std::shared_ptr<StructuredBuffer>> _frameBuffer; // 전체 본 프레임 정보

	void CreateVertexBuffer(const std::vector<Vertex>& buffer);
	void CreateIndexBuffer(const std::vector<uint32>& buffer);
	void CreateBonesAndAnimations(class FBXLoader& loader);
	Matrix GetMatrix(FbxAMatrix& matrix);
public:
	Mesh();
	virtual ~Mesh();

	void Create(const std::vector<Vertex>& vertexBuffer, const std::vector<uint32>& indexBuffer);
	void Render(uint32 instanceCount = 1, uint32 idx = 0);
	void Render(std::shared_ptr<class InstancingBuffer>& buffer, uint32 idx = 0);

	static std::shared_ptr<Mesh> CreateFromFBX(const struct FbxMeshInfo* meshInfo, class FBXLoader& loader);

	uint32 GetSubsetCount() { return static_cast<uint32>(_vecIndexInfo.size()); }
	const std::vector<BoneInfo>* GetBones() { return &_bones; }
	uint32						GetBoneCount() { return static_cast<uint32>(_bones.size()); }
	const std::vector<AnimClipInfo>* GetAnimClip() { return &_animClips; }

	bool							IsAnimMesh() { return !_animClips.empty(); }
	std::shared_ptr<StructuredBuffer>	GetBoneFrameDataBuffer(int32 index = 0) { return _frameBuffer[index]; } // 전체 본 프레임 정보
	std::shared_ptr<StructuredBuffer>	GetBoneOffsetBuffer() { return  _offsetBuffer; }
};