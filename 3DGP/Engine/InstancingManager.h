#pragma once
#include "InstancingBuffer.h"

class GameObject;

class InstancingManager
{
	DECLARE_SINGLE(InstancingManager);

	std::map<uint64/*instanceId*/, std::shared_ptr<InstancingBuffer>> _buffers;

	void AddParam(uint64 instanceId, InstancingParams& data);
public:
	void Render(std::vector<std::shared_ptr<GameObject>>& gameObjects);

	void ClearBuffer();
	void Clear() { _buffers.clear(); }
};