#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"

#include "Engine.h"
#include "Material.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"

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
	if (_activeScene)
		_activeScene->Render();
}

void SceneManager::LoadScene(std::wstring sceneName)
{
	// TODO : 기존 Scene 정리
	// TODO : 파일에서 Scene 정보 로드

	_activeScene = LoadTestScene();

	_activeScene->Awake();
	_activeScene->Start();
}

void SceneManager::SetLayerName(uint8 index, const std::wstring& name)
{
	// 기존 데이터 삭제
	const std::wstring& prevName = _layerNames[index];
	_layerIndex.erase(prevName);

	_layerNames[index] = name;
	_layerIndex[name] = index;
}

uint8 SceneManager::LayerNameToIndex(const std::wstring& name)
{
	auto findIt = _layerIndex.find(name);
	if (findIt == _layerIndex.end())
		return 0;

	return findIt->second;
}

std::shared_ptr<Scene> SceneManager::LoadTestScene()
{
#pragma region LayerMask
	SetLayerName(0, L"Default");
	SetLayerName(1, L"UI");
#pragma endregion

	std::shared_ptr<Scene> scene = std::make_shared<Scene>();

#pragma region Camera
	std::shared_ptr<GameObject> camera = std::make_shared<GameObject>();
	camera->SetName(L"Main_Camera");
	camera->AddComponent(std::make_shared<Transform>());
	camera->AddComponent(std::make_shared<Camera>());
	camera->AddComponent(std::make_shared<TestCameraScript>());
	camera->GetTransform()->SetLocalPosition(Vec3(0.f, 0.f, 0.f));
	uint8 layerIndex = GET_SINGLE(SceneManager)->LayerNameToIndex(L"UI");
	camera->GetCamera()->SetCullingMaskLayerOnOff(layerIndex, true); // UI는 안 찍음
	scene->AddGameObject(camera);
#pragma endregion

#pragma region UI_Camera
	{
		std::shared_ptr<GameObject> camera = std::make_shared<GameObject>();
		camera->SetName(L"Orthographic_Camera");
		camera->AddComponent(std::make_shared<Transform>());
		camera->AddComponent(std::make_shared<Camera>()); // Near=1, Far=1000, 800*600
		camera->GetTransform()->SetLocalPosition(Vec3(0.f, 0.f, 0.f));
		camera->GetCamera()->SetProjectionType(PROJECTION_TYPE::ORTHOGRAPHIC);
		uint8 layerIndex = GET_SINGLE(SceneManager)->LayerNameToIndex(L"UI");
		camera->GetCamera()->SetCullingMaskAll(); // 다 끄고
		camera->GetCamera()->SetCullingMaskLayerOnOff(layerIndex, false); // UI만 찍음
		scene->AddGameObject(camera);
	}
#pragma endregion

#pragma region SkyBox
	{
		std::shared_ptr<GameObject> skybox = std::make_shared<GameObject>();
		skybox->AddComponent(std::make_shared<Transform>());
		skybox->SetCheckFrustum(false);
		std::shared_ptr<MeshRenderer> meshRenderer = std::make_shared<MeshRenderer>();
		{
			std::shared_ptr<Mesh> sphereMesh = GET_SINGLE(Resources)->LoadSphereMesh();
			meshRenderer->SetMesh(sphereMesh);
		}
		{
			std::shared_ptr<Shader> shader = GET_SINGLE(Resources)->Get<Shader>(L"Skybox");
			std::shared_ptr<Texture> texture = GET_SINGLE(Resources)->Load<Texture>(L"Sky01", L"..\\Resources\\Texture\\Sky01.jpg");
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(0, texture);
			meshRenderer->SetMaterial(material);
		}
		skybox->AddComponent(meshRenderer);
		scene->AddGameObject(skybox);
	}
#pragma endregion

#pragma region Cube
	{
		std::shared_ptr<GameObject> sphere = std::make_shared<GameObject>();
		sphere->AddComponent(std::make_shared<Transform>());
		sphere->GetTransform()->SetLocalScale(Vec3(100.f, 100.f, 100.f));
		sphere->GetTransform()->SetLocalPosition(Vec3(0.f, 0.f, 150.f));
		std::shared_ptr<MeshRenderer> meshRenderer = std::make_shared<MeshRenderer>();
		{
			std::shared_ptr<Mesh> sphereMesh = GET_SINGLE(Resources)->LoadCubeMesh();
			meshRenderer->SetMesh(sphereMesh);
		}
		{
			std::shared_ptr<Shader> shader = GET_SINGLE(Resources)->Get<Shader>(L"Deferred");
			std::shared_ptr<Texture> texture = GET_SINGLE(Resources)->Load<Texture>(L"Metal_Pattern", L"..\\Resources\\Texture\\Metal_Pattern.png");
			std::shared_ptr<Texture> texture2 = GET_SINGLE(Resources)->Load<Texture>(L"Metal_Pattern_Normal", L"..\\Resources\\Texture\\Metal_Pattern_Normal.png");
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(0, texture);
			material->SetTexture(1, texture2);
			meshRenderer->SetMaterial(material);
		}
		sphere->AddComponent(meshRenderer);
		scene->AddGameObject(sphere);
	}
#pragma endregion

#pragma region UI_Test
	for (int32 i = 0; i < 3; i++)
	{
		std::shared_ptr<GameObject> sphere = std::make_shared<GameObject>();
		sphere->SetLayerIndex(GET_SINGLE(SceneManager)->LayerNameToIndex(L"UI")); // UI
		sphere->AddComponent(std::make_shared<Transform>());
		sphere->GetTransform()->SetLocalScale(Vec3(100.f, 100.f, 100.f));
		sphere->GetTransform()->SetLocalPosition(Vec3(-350.f + (i * 160),  250.f, 500.f));
		std::shared_ptr<MeshRenderer> meshRenderer = std::make_shared<MeshRenderer>();
		{
			std::shared_ptr<Mesh> mesh = GET_SINGLE(Resources)->LoadRectangleMesh();
			meshRenderer->SetMesh(mesh);
		}
		{
			std::shared_ptr<Shader> shader = GET_SINGLE(Resources)->Get<Shader>(L"Forward");
			std::shared_ptr<Texture> texture = GEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::G_BUFFER)->GetRTTexture(i);
			std::shared_ptr<Material> material = std::make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(0, texture);
			meshRenderer->SetMaterial(material);
		}
		sphere->AddComponent(meshRenderer);
		scene->AddGameObject(sphere);
	}
#pragma endregion

#pragma region Green Directional Light
	{
		std::shared_ptr<GameObject> light = std::make_shared<GameObject>();
		light->AddComponent(std::make_shared<Transform>());
		//light->GetTransform()->SetLocalPosition(Vec3(0.f, 150.f, 150.f));
		light->AddComponent(std::make_shared<Light>());
		light->GetLight()->SetLightDirection(Vec3(1.f, 0.f, 1.f));
		light->GetLight()->SetLightType(LIGHT_TYPE::DIRECTIONAL_LIGHT);
		light->GetLight()->SetDiffuse(Vec3(0.5f, 0.5f, 0.5f));
		light->GetLight()->SetAmbient(Vec3(0.1f, 0.1f, 0.1f));
		light->GetLight()->SetSpecular(Vec3(0.1f, 0.1f, 0.1f));

		scene->AddGameObject(light);
	}

#pragma endregion

	return scene;
}