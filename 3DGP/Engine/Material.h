#pragma once

class Shader;
class Texture;

enum
{
	MATERIAL_INT_COUNT = 5,
	MATERIAL_FLOAT_COUNT = 5,
	MATERIAL_TEXTURE_COUNT = 5,
};

struct MaterialParams
{
	void SetInt(uint8 index, int32 value) { intParams[index] = value; }
	void SetFloat(uint8 index, float value) { floatParams[index] = value; }

	// ũ�� ���� 5
	std::array<int32, MATERIAL_INT_COUNT> intParams;
	std::array<float, MATERIAL_FLOAT_COUNT> floatParams;
};

class Material
{
	std::shared_ptr<Shader> _shader;
	MaterialParams _params;
	std::array<std::shared_ptr<Texture>, MATERIAL_TEXTURE_COUNT> _textures;
public:
	std::shared_ptr<Shader> GetShader() { return _shader; }

	void SetShader(std::shared_ptr<Shader> shader) { _shader = shader; }
	void SetInt(uint8 index, int32 value) { _params.SetInt(index, value); }
	void SetFloat(uint8 index, float value) { _params.SetFloat(index, value); }
	void SetTexture(uint8 index, std::shared_ptr<Texture> texture) { _textures[index] = texture; }

	void PushData();
};

