#pragma once
#include "Component.h"
class Mesh;
class Material;

// [32][32]
union InstanceID
{
	struct
	{
		uint32 meshID;
		uint32 materialID;
	};
	uint64 id;
};

class MeshRenderer : public Component
{
	std::shared_ptr<Mesh> _mesh;
	std::shared_ptr<Material> _material;
public:
	MeshRenderer();
	virtual ~MeshRenderer();

	std::shared_ptr<Material> GetMaterial() { return _material; }

	void SetMesh(std::shared_ptr<Mesh> mesh) { _mesh = mesh; }
	void SetMaterial(std::shared_ptr<Material> material) { _material = material; }

	void Render();
	void Render(std::shared_ptr<class InstancingBuffer>& buffer);

	uint64 GetInstanceID();
};