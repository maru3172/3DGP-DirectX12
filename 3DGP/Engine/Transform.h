#pragma once
#include "Component.h"

struct TransformMatrix
{
	Vec4 offset;
};

class Transform : public Component
{
	// TODO : World ��ġ ����

public:
	Transform();
	virtual ~Transform();

	// TODO : �°� Parent/Child ����
};