#pragma once
#include "Component.h"
#include "Mesh.h"

class Material;
class StructuredBuffer;
class Mesh;

class Animator : public Component
{
	const std::vector<BoneInfo>* _bones;
	const std::vector<AnimClipInfo>* _animClips;

	float							_updateTime = 0.f;
	int32							_clipIndex = 0;
	int32							_frame = 0;
	int32							_nextFrame = 0;
	float							_frameRatio = 0;

	std::shared_ptr<Material>			_computeMaterial;
	std::shared_ptr<StructuredBuffer>	_boneFinalMatrix;  // Ư�� �������� ���� ���
	bool							_boneFinalUpdated = false;
public:
	Animator();
	virtual ~Animator();

	void SetBones(const std::vector<BoneInfo>* bones) { _bones = bones; }
	void SetAnimClip(const std::vector<AnimClipInfo>* animClips);
	void PushData();

	int32 GetAnimCount() { return static_cast<uint32>(_animClips->size()); }
	int32 GetCurrentClipIndex() { return _clipIndex; }
	void Play(uint32 idx);

	virtual void FinalUpdate() override;
};
