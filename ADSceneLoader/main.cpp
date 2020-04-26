#include "SceneLoader.h"

int main(int argc, char** argv)
{
	// Command List validation
	if (argc < 2) {
		std::cout << "Specify a scene file to load.\n";
		return EXIT_SUCCESS;
	}

	std::string scenename = std::string(argv[1]);

	SceneLoader loader;
	if (!loader.LoadScene("scenes/Base.unity"))
	{
		std::cout << "Failed to load scene file: " << scenename << "\n";
	}

	// Process scene
	loader.ProcessScene();

	// Write to file
	loader.ExportADScene();

	return EXIT_SUCCESS;
}