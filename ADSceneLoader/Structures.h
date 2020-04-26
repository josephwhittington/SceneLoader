#pragma once

struct FLOAT2
{
	float x, y;
};

struct FLOAT3
{
	float x, y, z;
};

struct FLOAT4
{
	float x, y, z, w;
};

struct GameObject
{
	char name[128];
	FLOAT3 position;
	FLOAT3 rotation;
	FLOAT3 scale;
};