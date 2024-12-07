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

std::shared_ptr<Scene> SceneManager::LoadTestScene()
{
	std::shared_ptr<Scene> scene = std::make_shared<Scene>();

#pragma region Camera
	std::shared_ptr<GameObject> camera = std::make_shared<GameObject>();
	camera->AddComponent(std::make_shared<Transform>());
	camera->AddComponent(std::make_shared<Camera>());
	camera->AddComponent(std::make_shared<TestCameraScript>());
	camera->GetTransform()->SetLocalPosition(Vec3(0.f, 0.f, 0.f));
	scene->AddGameObject(camera);
#pragma endregion

#pragma region SkyBox
	{
		std::shared_ptr<GameObject> skybox = std::make_shared<GameObject>();
		skybox->AddComponent(std::make_shared<Transform>());
		std::shared_ptr<MeshRenderer> meshRenderer = std::make_shared<MeshRenderer>();
		{
			std::shared_ptr<Mesh> sphereMesh = GET_SINGLE(Resources)->LoadSphereMesh();
			meshRenderer->SetMesh(sphereMesh);
		}
		{
			std::shared_ptr<Shader> shader = std::make_shared<Shader>();
			std::shared_ptr<Texture> texture = std::make_shared<Texture>();
			shader->Init(L"..\\Resources\\Shader\\skybox.hlsli",
				{ RASTERIZER_TYPE::CULL_NONE, DEPTH_STENCIL_TYPE::LESS_EQUAL });
			texture->Init(L"..\\Resources\\Texture\\Sky01.jpg");
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
			std::shared_ptr<Shader> shader = std::make_shared<Shader>();
			std::shared_ptr<Texture> texture = std::make_shared<Texture>();
			std::shared_ptr<Texture> texture2 = std::make_shared<Texture>();
			shader->Init(L"..\\Resources\\Shader\\default.hlsli");
			texture->Init(L"..\\Resources\\Texture\\Metal_Pattern.png");
			texture2->Init(L"..\\Resources\\Texture\\Metal_Pattern_Normal.png");
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

//#pragma region Red Point Light
//	{
//		std::shared_ptr<GameObject> light = std::make_shared<GameObject>();
//		light->AddComponent(std::make_shared<Transform>());
//		light->GetTransform()->SetLocalPosition(Vec3(150.f, 150.f, 150.f));
//		light->AddComponent(std::make_shared<Light>());
//		//light->GetLight()->SetLightDirection(Vec3(0.f, -1.f, 0.f));
//		light->GetLight()->SetLightType(LIGHT_TYPE::POINT_LIGHT);
//		light->GetLight()->SetDiffuse(Vec3(1.f, 0.1f, 0.1f));
//		light->GetLight()->SetAmbient(Vec3(0.1f, 0.f, 0.f));
//		light->GetLight()->SetSpecular(Vec3(0.1f, 0.1f, 0.1f));
//		light->GetLight()->SetLightRange(10000.f);
//		//light->GetLight()->SetLightAngle(XM_PI / 4);
//		scene->AddGameObject(light);
//	}
//#pragma endregion
//
//#pragma region Blue Spot Light
//	{
//		std::shared_ptr<GameObject> light = std::make_shared<GameObject>();
//		light->AddComponent(std::make_shared<Transform>());
//		light->GetTransform()->SetLocalPosition(Vec3(-150.f, 0.f, 150.f));
//		light->AddComponent(std::make_shared<Light>());
//		light->GetLight()->SetLightDirection(Vec3(1.f, 0.f, 0.f));
//		light->GetLight()->SetLightType(LIGHT_TYPE::SPOT_LIGHT);
//		light->GetLight()->SetDiffuse(Vec3(0.f, 0.1f, 1.f));
//		//light->GetLight()->SetAmbient(Vec3(0.f, 0.f, 0.1f));
//		light->GetLight()->SetSpecular(Vec3(0.1f, 0.1f, 0.1f));
//		light->GetLight()->SetLightRange(10000.f);
//		light->GetLight()->SetLightAngle(XM_PI / 4);
//		scene->AddGameObject(light);
//	}
//#pragma endregion

	return scene;
}