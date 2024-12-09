#pragma once

enum class OBJECT_TYPE : uint8
{
	NONE,
	GAMEOBJECT, // PREFAB
	COMPONENT,
	MATERIAL,
	MESH,
	SHADER,
	TEXTURE,

	END
};

enum
{
	OBJECT_TYPE_COUNT = static_cast<uint8>(OBJECT_TYPE::END)
};

class Object
{
protected:
	OBJECT_TYPE _objectType = OBJECT_TYPE::NONE;
	std::wstring _name;
	uint32 _id = 0;

	friend class Resources;
	virtual void Load(const std::wstring& path) { }
	virtual void Save(const std::wstring& path) { }
public:
	Object(OBJECT_TYPE type);
	virtual ~Object();

	OBJECT_TYPE GetType() { return _objectType; }

	void SetName(const std::wstring& name) { _name = name; }
	const std::wstring& GetName() { return _name; }

	uint32 GetID() { return _id; }

	// TODO : Instantiate
};

