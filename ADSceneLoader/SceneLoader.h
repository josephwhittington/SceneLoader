#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <assert.h>

class SceneLoader
{
public:
	SceneLoader() = default;
	~SceneLoader() = default;

	bool LoadScene(std::string scenename);
	bool ProcessScene();

private:
	std::ifstream scene;
};