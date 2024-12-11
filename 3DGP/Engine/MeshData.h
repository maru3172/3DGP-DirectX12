#pragma once
#include "Object.h"

class Mesh;
class Material;
class GameObject;

struct MeshRenderInfo
{
	std::shared_ptr<Mesh> mesh;
	std::vector<std::shared_ptr<Material>> materials;
};

class MeshData : public Object
{
	std::shared_ptr<Mesh>				_mesh;
	std::vector<std::shared_ptr<Material>>	_materials;

	std::vector<MeshRenderInfo> _meshRenders;
public:
	MeshData();
	virtual ~MeshData();

	static std::shared_ptr<MeshData> LoadFromFBX(const std::wstring& path);

	virtual void Load(const std::wstring& path);
	virtual void Save(const std::wstring& path);

	std::vector<std::shared_ptr<GameObject>> Instantiate();
};
