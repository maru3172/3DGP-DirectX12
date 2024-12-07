#pragma once
#include "Component.h"
#include "Object.h"

class Transform;
class MeshRenderer;
class Camera;
class Light;
class MonoBehaviour;

class GameObject : public Object, public std::enable_shared_from_this<GameObject>
{
	std::array<std::shared_ptr<Component>, FIXED_COMPONENT_COUNT> _components;
	std::vector<std::shared_ptr<MonoBehaviour>> _scripts;

	bool _checkFrustum = true;
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
	std::shared_ptr<Light> GetLight();

	void AddComponent(std::shared_ptr<Component> component);
	
	void SetCheckFrustum(bool checkFrustum) { _checkFrustum = checkFrustum; }
	bool GetCheckFrustum() { return _checkFrustum; }
};

