#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <assert.h>

#include "Structures.h"
#include "Helpers.h"

class SceneLoader
{
public:
	SceneLoader() = default;
	~SceneLoader() = default;

	bool LoadScene(std::string scenename);
	bool ProcessScene();

	// Export
	bool ExportADScene();

private:
	void PopulateGameObjectFromPrefabInstance();

	// Helpers
	bool HasProp(std::string line, std::string prop);
	int ExtractFileID(std::string str);
	std::string ExtractStringValue(std::string line);
	int ExtractIntValue(std::string line);
	float ExtractFloatValue(std::string line);
	FLOAT3 ExtractPos(int first_axis);
	FLOAT3 ExtractRotation(int first_axis);
	FLOAT3 ExtractScale(int first_axis);

	// Export stuff
	std::string GenerateGameObjectString(GameObject& obj);

private:
	std::ifstream scene;

	// Collections
	std::vector<GameObject> objects;
};

// NOTE: 
/*
	- Axis order can be different
*/