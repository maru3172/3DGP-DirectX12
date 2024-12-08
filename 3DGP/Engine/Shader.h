#pragma once
#include "Object.h"

enum class SHADER_TYPE : uint8
{
	DEFERRED,
	FORWARD,
	LIGHTING,
	PARTICLE,
	COMPUTE,
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
	NO_DEPTH_TEST, // 깊이 테스트(X) + 깊이 기록(O)
	NO_DEPTH_TEST_NO_WRITE, // 깊이 테스트(X) + 깊이 기록(X)
	LESS_NO_WRITE, // 깊이 테스트(O) + 깊이 기록(X)
};

enum class BLEND_TYPE : uint8
{
	DEFAULT,
	ALPHA_BLEND,
	ONE_TO_ONE_BLEND,
	END,
};

struct ShaderInfo
{
	SHADER_TYPE shaderType = SHADER_TYPE::FORWARD;
	RASTERIZER_TYPE rasterizerType = RASTERIZER_TYPE::CULL_BACK;
	DEPTH_STENCIL_TYPE depthStencilType = DEPTH_STENCIL_TYPE::LESS;
	BLEND_TYPE blendType = BLEND_TYPE::DEFAULT;
	D3D_PRIMITIVE_TOPOLOGY topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
};

// 뭘 해야할지 기술하는 기술서
class Shader : public Object
{
	ShaderInfo _info;
	ComPtr<ID3D12PipelineState>			_pipelineState;

	// Graphics Shader
	ComPtr<ID3DBlob>					_vsBlob;
	ComPtr<ID3DBlob>					_psBlob;
	ComPtr<ID3DBlob>					_gsBlob;
	ComPtr<ID3DBlob>					_errBlob;
	D3D12_GRAPHICS_PIPELINE_STATE_DESC  _graphicsPipelineDesc = {};

	// Compute Shader
	ComPtr<ID3DBlob>					_csBlob;
	D3D12_COMPUTE_PIPELINE_STATE_DESC   _computePipelineDesc = {};

	void CreateShader(const std::wstring& path, const std::string& name, const std::string& version, ComPtr<ID3DBlob>& blob, D3D12_SHADER_BYTECODE& shaderByteCode);
	void CreateVertexShader(const std::wstring& path, const std::string& name, const std::string& version);
	void CreatePixelShader(const std::wstring& path, const std::string& name, const std::string& version);
	void CreateGeometryShader(const std::wstring& path, const std::string& name, const std::string& version);
public:
	Shader();
	virtual ~Shader();

	void CreateGraphicsShader(const std::wstring& path, ShaderInfo info = ShaderInfo(), const std::string& vs = "VS_Main", const std::string& ps = "PS_Main", const std::string& gs = "");
	void CreateComputeShader(const std::wstring& path, const std::string& name, const std::string& version);
	void Update();

	SHADER_TYPE GetShaderType() { return _info.shaderType; }

	static D3D12_PRIMITIVE_TOPOLOGY_TYPE GetTopologyType(D3D_PRIMITIVE_TOPOLOGY topology);
};
