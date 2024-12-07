#pragma once

class Scene;

enum
{
	MAX_LAYER = 32
};

class SceneManager
{
	DECLARE_SINGLE(SceneManager);

	std::shared_ptr<Scene> _activeScene;

	std::array<std::wstring, MAX_LAYER> _layerNames;
	std::map<std::wstring, uint8> _layerIndex;

	std::shared_ptr<Scene> LoadTestScene();

public:
	void Update();
	void Render();
	void LoadScene(std::wstring sceneName);

	void SetLayerName(uint8 index, const std::wstring& name);
	const std::wstring& IndexToLayerName(uint8 index) { return _layerNames[index]; }
	uint8 LayerNameToIndex(const std::wstring& name);

	std::shared_ptr<Scene> GetActiveScene() { return _activeScene; }
};