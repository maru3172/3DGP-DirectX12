#pragma once

class GameObject;

class Scene
{
	std::vector<std::shared_ptr<GameObject>> _gameObjects;
public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();

	void AddGameObject(std::shared_ptr<GameObject> gameObject);
	void RemoveGameObject(std::shared_ptr<GameObject> gameObject);
};

