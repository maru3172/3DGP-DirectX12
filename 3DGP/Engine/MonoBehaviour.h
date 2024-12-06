#pragma once
#include "Component.h"

class MonoBehaviour :public Component
{
	// 다른 곳에서 못 부르고 마지막에 업데이트를 진행하게만 하게끔 쉴드치기
	virtual void FinalUpdate() sealed { }
public:
	MonoBehaviour();
	virtual ~MonoBehaviour();
};