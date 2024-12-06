#pragma once
#include "Component.h"
class Transform;
class MeshRenderer;
class MonoBehaviour;

class GameObject : public std::enable_shared_from_this<GameObject>
{
	std::array<std::shared_ptr<Component>, FIXED_COMPONENT_COUNT> _components;
	std::vector<std::shared_ptr<MonoBehaviour>> _scripts;
public:
	GameObject();
	virtual ~GameObject();

	void Init();

	void Awake();
	void Start();
	void Update();
	void LateUpdate();

	std::shared_ptr<Transform> GetTransform();

	void AddComponent(std::shared_ptr<Component> component);
};

