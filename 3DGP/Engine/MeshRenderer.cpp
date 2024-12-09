#include "pch.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"
#include "InstancingBuffer.h"

MeshRenderer::MeshRenderer() : Component(COMPONENT_TYPE::MESH_RENDERER)
{

}

MeshRenderer::~MeshRenderer()
{

}

void MeshRenderer::Render()
{
	GetTransform()->PushData();
	_material->PushGraphicsData();
	_mesh->Render();
}

void MeshRenderer::Render(std::shared_ptr<InstancingBuffer>& buffer)
{
	buffer->PushData();
	_material->PushGraphicsData();
	_mesh->Render(buffer);
}

uint64 MeshRenderer::GetInstanceID()
{
	if (_mesh == nullptr || _material == nullptr)
		return 0;

	//uint64 id = (_mesh->GetID() << 32) | _material->GetID();
	InstanceID instanceID{ _mesh->GetID(), _material->GetID() };
	return instanceID.id;
}