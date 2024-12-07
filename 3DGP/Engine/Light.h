#pragma once
#include "Component.h"

enum class LIGHT_TYPE : uint8
{
	DIRECTIONAL_LIGHT,
	POINT_LIGHT,
	SPOT_LIGHT,
};

struct LightColor
{
	Vec4 diffuse;
	Vec4 ambient;
	Vec4 specular;
};

struct LightInfo
{
	LightColor color;
	Vec4 position;
	Vec4 direction;
	int32 lightType;
	float range;
	float angle;
	int32 padding;
};

struct LightParams
{
	uint32 lightCount;
	Vec3 padding;
	LightInfo lights[50];
};

class Light : public Component
{
	LightInfo _lightInfo = {};
public:
	Light();
	virtual ~Light();

	virtual void FinalUpdate() override;

	const LightInfo& GetLightInfo() { return _lightInfo; }

	void SetLightDirection(const Vec3& direction) { _lightInfo.direction = direction; }

	void SetDiffuse(const Vec3& diffuse) { _lightInfo.color.diffuse = diffuse; }
	void SetAmbient(const Vec3& ambient) { _lightInfo.color.ambient = ambient; }
	void SetSpecular(const Vec3& specular) { _lightInfo.color.specular = specular; }

	void SetLightType(LIGHT_TYPE type) { _lightInfo.lightType = static_cast<int32>(type); }
	void SetLightRange(float range) { _lightInfo.range = range; }
	void SetLightAngle(float angle) { _lightInfo.angle = angle; }
};