#pragma once
#include "Component.h"

class MonoBehaviour :public Component
{
	// �ٸ� ������ �� �θ��� �������� ������Ʈ�� �����ϰԸ� �ϰԲ� ����ġ��
	virtual void FinalUpdate() sealed { }
public:
	MonoBehaviour();
	virtual ~MonoBehaviour();
};