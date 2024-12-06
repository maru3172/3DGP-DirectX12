#include "pch.h"
#include "GameObject.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "MonoBehaviour.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

void GameObject::Init()
{
	AddComponent(std::make_shared<Transform>());
}

void GameObject::Awake()
{
	for (std::shared_ptr<Component>& component : _components)
	{
		if (component)
			component->Awake();
	}

	for (std::shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->Awake();
	}
}

void GameObject::Start()
{
	for (std::shared_ptr<Component>& component : _components)
	{
		if (component)
			component->Start();
	}

	for (std::shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->Start();
	}
}

void GameObject::Update()
{
	for (std::shared_ptr<Component>& component : _components)
	{
		if (component)
			component->Update();
	}

	for (std::shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->Update();
	}
}

void GameObject::LateUpdate()
{
	for (std::shared_ptr<Component>& component : _components)
	{
		if (component)
			component->LateUpdate();
	}

	for (std::shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->LateUpdate();
	}
}

std::shared_ptr<Transform> GameObject::GetTransform()
{
	uint8 index = static_cast<uint8>(COMPONENT_TYPE::TRANSFORM);
	return static_pointer_cast<Transform>(_components[index]);
}

void GameObject::AddComponent(std::shared_ptr<Component> component)
{
	component->SetGameObject(shared_from_this());

	uint8 index = static_cast<uint8>(component->GetType());
	if (index < FIXED_COMPONENT_COUNT)
	{
		_components[index] = component;
	}
	else
	{
		_scripts.push_back(dynamic_pointer_cast<MonoBehaviour>(component));
	}
}