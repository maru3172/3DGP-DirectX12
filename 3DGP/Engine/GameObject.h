#pragma once
#include "Component.h"
class Transform;
class MeshRenderer;
class Camera;
class MonoBehaviour;

class GameObject : public std::enable_shared_from_this<GameObject>
{
	std::array<std::shared_ptr<Component>, FIXED_COMPONENT_COUNT> _components;
	std::vector<std::shared_ptr<MonoBehaviour>> _scripts;
public:
	GameObject();
	virtual ~GameObject();

	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();

	std::shared_ptr<Component> GetFixedComponent(COMPONENT_TYPE type);

	std::shared_ptr<Transform> GetTransform();
	std::shared_ptr<MeshRenderer> GetMeshRenderer();
	std::shared_ptr<Camera> GetCamera();

	void AddComponent(std::shared_ptr<Component> component);
};

