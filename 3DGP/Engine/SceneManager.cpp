#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"

#include "Engine.h"
#include "Material.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"

#include "TestCameraScript.h"
#include "Resources.h"

void SceneManager::Update()
{
	if (_activeScene == nullptr)
		return;

	_activeScene->Update();
	_activeScene->LateUpdate();
	_activeScene->FinalUpdate();
}

void SceneManager::Render()
{
	if (_activeScene == nullptr)
		return;

	const std::vector<std::shared_ptr<GameObject>>& gameObjects = _activeScene->GetGameObjects();
	for (auto& gameObject : gameObjects)
	{
		if (gameObject->GetCamera() == nullptr)
			continue;

		gameObject->GetCamera()->Render();
	}
}

void SceneManager::LoadScene(std::wstring sceneName)
{
	// TODO : 기존 Scene 정리
	// TODO : 파일에서 Scene 정보 로드

	_activeScene = LoadTestScene();

	_activeScene->Awake();
	_activeScene->Start();
}

std::shared_ptr<Scene> SceneManager::LoadTestScene()
{
	std::shared_ptr<Scene> scene = std::make_shared<Scene>();

#pragma region Camera
	std::shared_ptr<GameObject> camera = std::make_shared<GameObject>();
	camera->AddComponent(std::make_shared<Transform>());
	camera->AddComponent(std::make_shared<Camera>());
	camera->AddComponent(std::make_shared<TestCameraScript>());
	camera->GetTransform()->SetLocalPosition(Vec3(0.f, 100.f, 0.f));
	scene->AddGameObject(camera);
#pragma endregion

#pragma region Sphere
	{
		std::shared_ptr<GameObject> sphere = std::make_shared<GameObject>();
		sphere->AddComponent(std::make_shared<Transform>());
		sphere->GetTransform()->SetLocalScale(Vec3(100.f, 100.f, 100.f));
		sphere->GetTransform()->SetLocalPosition(Vec3(0.f, 100.f, 200.f));
		std::shared_ptr<MeshRenderer> meshRenderer = std::make_shared<MeshRenderer>();
		{
			std::shared_ptr<Mesh> sphereMesh = GET_SINGLE(Resources)->LoadSphereMesh();
			meshRenderer->SetMesh(sphereMesh);
		}
		{
			std::shared_ptr<Shader> shader = std::make_shared<Shader>();
			std::shared_ptr<Texture> texture = std::make_shared<Texture>();
			shader->Init(L"..\\Resources\\Shader\\default.hlsli");
			texture->Init(L"..\\Resources\\Texture\\BackGround.jpg");
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(0, texture);
			meshRenderer->SetMaterial(material);
		}
		sphere->AddComponent(meshRenderer);
		scene->AddGameObject(sphere);
	}
#pragma endregion

#pragma region Cube
	{
		std::shared_ptr<GameObject> sphere = std::make_shared<GameObject>();
		sphere->AddComponent(std::make_shared<Transform>());
		sphere->GetTransform()->SetLocalScale(Vec3(100.f, 100.f, 100.f));
		sphere->GetTransform()->SetLocalPosition(Vec3(150.f, 100.f, 200.f));
		std::shared_ptr<MeshRenderer> meshRenderer = std::make_shared<MeshRenderer>();
		{
			std::shared_ptr<Mesh> sphereMesh = GET_SINGLE(Resources)->LoadCubeMesh();
			meshRenderer->SetMesh(sphereMesh);
		}
		{
			std::shared_ptr<Shader> shader = std::make_shared<Shader>();
			std::shared_ptr<Texture> texture = std::make_shared<Texture>();
			shader->Init(L"..\\Resources\\Shader\\default.hlsli");
			texture->Init(L"..\\Resources\\Texture\\BackGround.jpg");
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(0, texture);
			meshRenderer->SetMaterial(material);
		}
		sphere->AddComponent(meshRenderer);
		scene->AddGameObject(sphere);
	}
#pragma endregion

	return scene;
}