#pragma once
#include "Component.h"

struct TransformMatrix
{
	Vec4 offset;
};

class Transform : public Component
{
	// TODO : World 위치 관련

public:
	Transform();
	virtual ~Transform();

	// TODO : 온갖 Parent/Child 관계
};