#pragma once

class Scene;

class SceneManager
{
	DECLARE_SINGLE(SceneManager);

	std::shared_ptr<Scene> _activeScene;

	std::shared_ptr<Scene> LoadTestScene();
public:
	void Update();
	void LoadScene(std::wstring sceneName);

	std::shared_ptr<Scene> GetActiveScene() { return _activeScene; }
};