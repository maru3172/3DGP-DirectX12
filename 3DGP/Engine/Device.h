#pragma once

// 인력사무소 같은 것이다
// 받아와서 다양한 화면의 기능을 지원한다
class Device
{
	// Com (Component Object Model)
	// DX의 프로그래밍 언어 독립성과 하위 호환성을 가능하게 해주는 기술
	// COM 객체(COM인터페이스)를 사용, 세부사항은 우리에게 숨겨짐
	// ComPtr - 일종의 스마트 포인터
	ComPtr<ID3D12Debug> _debugController;
	ComPtr<IDXGIFactory> _dxgi; // 화면 관련 기능들
	ComPtr<ID3D12Device> _device; // 각종 개체 생성
public:
	void Init();

	ComPtr<IDXGIFactory> GetDXGI() { return _dxgi; }
	ComPtr<ID3D12Device> GetDevice() { return _device; }
};