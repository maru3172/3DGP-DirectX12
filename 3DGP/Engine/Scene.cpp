#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"
#include "Engine.h"
#include "ConstantBuffer.h"
#include "Light.h"

void Scene::Awake()
{
	for (const std::shared_ptr<GameObject>& gameObject : _gameObjects)
	{
		gameObject->Awake();
	}
}

void Scene::Start()
{
	for (const std::shared_ptr<GameObject>& gameObject : _gameObjects)
	{
		gameObject->Start();
	}
}

void Scene::Update()
{
	for (const std::shared_ptr<GameObject>& gameObject : _gameObjects)
	{
		gameObject->Update();
	}
}

void Scene::LateUpdate()
{
	for (const std::shared_ptr<GameObject>& gameObject : _gameObjects)
	{
		gameObject->LateUpdate();
	}
}

void Scene::FinalUpdate()
{
	for (const std::shared_ptr<GameObject>& gameObject : _gameObjects)
	{
		gameObject->FinalUpdate();
	}
}

void Scene::Render()
{
	PushLightData();

	for (auto& gameObject : _gameObjects)
	{
		if (gameObject->GetCamera() == nullptr)
			continue;

		gameObject->GetCamera()->Render();
	}
}

void Scene::PushLightData()
{
	LightParams lightParams = {};
	
	for (auto& gameObject : _gameObjects)
	{
		if (gameObject->GetLight() == nullptr)
			continue;

		const LightInfo& lightInfo = gameObject->GetLight()->GetLightInfo();

		lightParams.lights[lightParams.lightCount] = lightInfo;
		lightParams.lightCount++;
	}

	CONST_BUFFER(CONSTANT_BUFFER_TYPE::GLOBAL)->SetGlobalData(&lightParams, sizeof(lightParams));
}

void Scene::AddGameObject(std::shared_ptr<GameObject> gameObject)
{
	_gameObjects.push_back(gameObject);
}

void Scene::RemoveGameObject(std::shared_ptr<GameObject> gameObject)
{
	auto findIt = std::find(_gameObjects.begin(), _gameObjects.end(), gameObject);
	if (findIt != _gameObjects.end())
	{
		_gameObjects.erase(findIt);
	}
}