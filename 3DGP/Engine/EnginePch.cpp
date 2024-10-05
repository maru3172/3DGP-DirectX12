#include "pch.h"
#include "EnginePch.h"
#include "Engine.h"

std::unique_ptr<Engine> GEngine = std::make_unique<Engine>(); // 엔진 헤더에서 전역 클래스 선언 및 가져옴