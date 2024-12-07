#pragma once
#include "Object.h"

// 뭘 해야할지 기술하는 기술서
class Shader : public Object
{
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

	void Init(const std::wstring& path);
	void Update();
};

