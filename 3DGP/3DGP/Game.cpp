#include "pch.h"
#include "Game.h"
#include "Engine.h"
#include "Material.h"

std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();

void Game::init(const WindowInfo& info)
{
	GEngine->Init(info);

	std::vector<Vertex> vec(4);
	vec[0].pos = Vec3(-0.5f, 0.5f, 0.5f);
	vec[0].color = Vec4(1.f, 0.f, 0.f, 1.f);
	vec[0].uv = Vec2(0.f, 0.f);
	vec[1].pos = Vec3(0.5f, 0.5f, 0.5f);
	vec[1].color = Vec4(0.f, 1.f, 0.f, 1.f);
	vec[1].uv = Vec2(1.f, 0.f);
	vec[2].pos = Vec3(0.5f, -0.5f, 0.5f);
	vec[2].color = Vec4(0.f, 0.f, 1.f, 1.f);
	vec[2].uv = Vec2(1.f, 1.f);
	vec[3].pos = Vec3(-0.5f, -0.5f, 0.5f);
	vec[3].color = Vec4(0.f, 1.f, 0.f, 1.f);
	vec[3].uv = Vec2(0.f, 1.f);

	std::vector<uint32> indexVec;
	{
		indexVec.push_back(0);
		indexVec.push_back(1);
		indexVec.push_back(2);
	}
	{
		indexVec.push_back(0);
		indexVec.push_back(2);
		indexVec.push_back(3);
	}

	mesh->Init(vec, indexVec);

	std::shared_ptr<Shader> shader = std::make_shared<Shader>();
	std::shared_ptr<Texture> texture = std::make_shared<Texture>();
	shader->Init(L"..\\Resources\\Shader\\default.hlsli");
	texture->Init(L"..\\Resources\\Texture\\background.jpg");

	std::shared_ptr<Material> material = std::make_shared<Material>();
	material->SetShader(shader);
	material->SetFloat(0, 0.3f);
	material->SetFloat(1, 0.4f);
	material->SetFloat(2, 0.3f);
	material->SetTexture(0, texture);
	mesh->SetMaterial(material);

	GEngine->GetCmdQueue()->WaitSync();
}

void Game::Update()
{
	GEngine->Update();
	GEngine->RenderBegin();

	{
		static Transform t = {};

		if (INPUT->GetButton(KEY_TYPE::W))
			t.offset.y += 1.f * DELTA_TIME;
		if (INPUT->GetButton(KEY_TYPE::S))
			t.offset.y -= 1.f * DELTA_TIME;
		if (INPUT->GetButton(KEY_TYPE::A))
			t.offset.x -= 1.f * DELTA_TIME;
		if (INPUT->GetButton(KEY_TYPE::D))
			t.offset.x += 1.f * DELTA_TIME;

		mesh->SetTransform(t);

		mesh->Render();
	}

	/*{
		Transform t;
		t.offset = Vec4(0.0f, 0.f, 0.3f, 0.f);
		mesh->SetTransform(t);

		mesh->SetTexture(texture);

		mesh->Render();
	}*/

	GEngine->RenderEnd();
}