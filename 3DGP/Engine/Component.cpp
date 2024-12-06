#include "pch.h"
#include "Component.h"
#include "GameObject.h"

Component::Component(COMPONENT_TYPE type) : _type(type)
{

}

Component::~Component()
{
}

std::shared_ptr<GameObject> Component::GetGameObject()
{
	return _gameObject.lock();
}

std::shared_ptr<Transform> Component::GetTransform()
{
	return _gameObject.lock()->GetTransform();
}