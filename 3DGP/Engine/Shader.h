#pragma once
#include "Object.h"

enum class SHADER_TYPE : uint8
{
	DEFERRED,
	FORWARD,
};

enum class RASTERIZER_TYPE
{
	CULL_NONE,
	CULL_FRONT,
	CULL_BACK,
	WIREFRAME,
};

enum class DEPTH_STENCIL_TYPE
{
	LESS,
	LESS_EQUAL,
	GREATER,
	GREATER_EQUAL,
};

struct ShaderInfo
{
	SHADER_TYPE shaderType = SHADER_TYPE::FORWARD;
	RASTERIZER_TYPE rasterizerType = RASTERIZER_TYPE::CULL_BACK;
	DEPTH_STENCIL_TYPE depthStencilType = DEPTH_STENCIL_TYPE::LESS;
	D3D12_PRIMITIVE_TOPOLOGY_TYPE topologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
};

// 뭘 해야할지 기술하는 기술서
class Shader : public Object
{
	ShaderInfo _info;

	ComPtr<ID3DBlob>					_vsBlob;
	ComPtr<ID3DBlob>					_psBlob;
	ComPtr<ID3DBlob>					_errBlob;

	ComPtr<ID3D12PipelineState>			_pipelineState;
	D3D12_GRAPHICS_PIPELINE_STATE_DESC  _pipelineDesc = {};

	void CreateShader(const std::wstring& path, const std::string& name, const std::string& version, ComPtr<ID3DBlob>& blob, D3D12_SHADER_BYTECODE& shaderByteCode);
	void CreateVertexShader(const std::wstring& path, const std::string& name, const std::string& version);
	void CreatePixelShader(const std::wstring& path, const std::string& name, const std::string& version);
public:
	Shader();
	virtual ~Shader();

	void Init(const std::wstring& path, ShaderInfo info = ShaderInfo());
	void Update();

	SHADER_TYPE GetShaderType() { return _info.shaderType; }
};

