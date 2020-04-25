#include "SceneLoader.h"
#include "definitions.h"

bool SceneLoader::LoadScene(std::string scenename)
{
	scene.open(scenename.c_str());
	assert(scene.is_open());

	if(!scene.is_open()) return false;
	return true;
}

bool SceneLoader::ProcessScene()
{
	int GO_COUNT = 0;
	string line;
	string other_line;
	while (std::getline(scene, line))
	{
		if (line.find(HEADER_GAME_OBJECT) != std::string::npos)
		{
			// Read the next line to see if it is a game object
			if()
		}
	}

	std::cout << "Game Object count: " << GO_COUNT << "\n";

	return true;
}
