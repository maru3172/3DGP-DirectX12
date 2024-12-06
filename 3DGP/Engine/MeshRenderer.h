#pragma once
#include "Component.h"
class Mesh;
class Material;

class MeshRenderer : public Component
{
	std::shared_ptr<Mesh> _mesh;
	std::shared_ptr<Material> _material;
public:
	MeshRenderer();
	virtual ~MeshRenderer();

	void SetMesh(std::shared_ptr<Mesh> mesh) { _mesh = mesh; }
	void SetMaterial(std::shared_ptr<Material> material) { _material = material; }

	virtual void Update() override { Render(); }

	void Render();
};