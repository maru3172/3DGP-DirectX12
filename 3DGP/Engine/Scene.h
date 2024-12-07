#pragma once

class GameObject;

class Scene
{
	std::vector<std::shared_ptr<GameObject>> _gameObjects;

	void PushLightData();
public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();

	void Render();

	void AddGameObject(std::shared_ptr<GameObject> gameObject);
	void RemoveGameObject(std::shared_ptr<GameObject> gameObject);

	const std::vector<std::shared_ptr<GameObject>>& GetGameObjects() { return _gameObjects; }
};