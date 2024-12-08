#pragma once
#include "GameObject.h"
#include "Material.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

class Resources
{
	DECLARE_SINGLE(Resources);

	using KeyObjMap = std::map<std::wstring/*key*/, std::shared_ptr<Object>>;
	std::array<KeyObjMap, OBJECT_TYPE_COUNT> _resources;

	void CreateDefaultShader();
public:
	void Init();

	template<typename T>
	std::shared_ptr<T> Load(const std::wstring& key, const std::wstring& path);

	template<typename T>
	bool Add(const std::wstring& key, std::shared_ptr<T> object);

	template<typename T>
	std::shared_ptr<T> Get(const std::wstring& Key);

	template<typename T>
	OBJECT_TYPE GetObjectType();

	std::shared_ptr<Mesh> LoadRectangleMesh();
	std::shared_ptr<Mesh> LoadCubeMesh();
	std::shared_ptr<Mesh> LoadSphereMesh();

	std::shared_ptr<Texture> CreateTexture(const std::wstring& name, DXGI_FORMAT format, uint32 width, uint32 height,
		const D3D12_HEAP_PROPERTIES& heapProperty, D3D12_HEAP_FLAGS heapFlags,
		D3D12_RESOURCE_FLAGS resFlags = D3D12_RESOURCE_FLAG_NONE, Vec4 clearColor = Vec4());

	std::shared_ptr<Texture> CreateTextureFromResource(const std::wstring& name, ComPtr<ID3D12Resource> tex2D);
};

template<typename T>
inline std::shared_ptr<T> Resources::Load(const std::wstring& key, const std::wstring& path)
{
	OBJECT_TYPE objectType = GetObjectType<T>();
	KeyObjMap& keyObjMap = _resources[static_cast<uint8>(objectType)];

	auto findIt = keyObjMap.find(key);
	if (findIt != keyObjMap.end())
		return static_pointer_cast<T>(findIt->second);

	std::shared_ptr<T> object = std::make_shared<T>();
	object->Load(path);
	keyObjMap[key] = object;

	return object;
}

template<typename T>
bool Resources::Add(const std::wstring& key, std::shared_ptr<T> object)
{
	OBJECT_TYPE objectType = GetObjectType<T>();
	KeyObjMap& keyObjMap = _resources[static_cast<uint8>(objectType)];

	auto findIt = keyObjMap.find(key);
	if (findIt != keyObjMap.end())
		return false;

	keyObjMap[key] = object;

	return true;
}

template<typename T>
std::shared_ptr<T> Resources::Get(const std::wstring& key)
{
	OBJECT_TYPE objectType = GetObjectType<T>();
	KeyObjMap& keyObjMap = _resources[static_cast<uint8>(objectType)];

	auto findIt = keyObjMap.find(key);
	if (findIt != keyObjMap.end())
		return static_pointer_cast<T>(findIt->second);

	return nullptr;
}

template<typename T>
inline OBJECT_TYPE Resources::GetObjectType()
{
	if (std::is_same_v<T, GameObject>)
		return OBJECT_TYPE::GAMEOBJECT;
	else if (std::is_same_v<T, Material>)
		return OBJECT_TYPE::MATERIAL;
	else if (std::is_same_v<T, Mesh>)
		return OBJECT_TYPE::MESH;
	else if (std::is_same_v<T, Shader>)
		return OBJECT_TYPE::SHADER;
	else if (std::is_same_v<T, Texture>)
		return OBJECT_TYPE::TEXTURE;
	else if (std::is_convertible_v<T, Component>)
		return OBJECT_TYPE::COMPONENT;
	else
		return OBJECT_TYPE::NONE;
}