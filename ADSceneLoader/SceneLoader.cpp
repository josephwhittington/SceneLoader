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
		if (HasProp(line, HEADER_GAME_OBJECT))
		{
			std::getline(scene, other_line);

			if (HasProp(other_line, OT_PREFAB_INST))
			{
				PopulateGameObjectFromPrefabInstance();
				GO_COUNT++;
			}
		}
	}

	std::cout << "Game Object count: " << GO_COUNT << "\n";

	return true;
}

bool SceneLoader::ExportADScene()
{
	std::ofstream file("scenes/exports/scene.adscenet");
	assert(file.is_open());

	if (!file.is_open())
	{
		std::cout << "Failed to create text output file" << std::endl;
	}

	// Write game objects
	string data = GenerateGameObjectString(objects[0]);
	file << data;

	file.close();

	return true;
}

void SceneLoader::PopulateGameObjectFromPrefabInstance()
{
	string line;
	string other_line;
	bool RUN = true;
	GameObject obj;
	Zeroize((char*)&obj, sizeof(GameObject));

	while (RUN)
	{
		std::getline(scene, line);

		// Read the next line to see if it is a game object
		if (HasProp(line, END_PREFAB_INST))
		{
			RUN = false;
		}
		else if (HasProp(line, PREFAB_NAME))
		{
			std::getline(scene, other_line);
			// get string value
			string b = ExtractStringValue(other_line).substr(1).append(".wobj");
			strcpy_s(obj.name, b.c_str());
		}
		else if (HasProp(line, PREFAB_POS_X) || HasProp(line, PREFAB_POS_Y) || HasProp(line, PREFAB_POS_Z))
		{
			int axis = -1;

			if (HasProp(line, PREFAB_POS_X)) axis = (int)AXIS::X;
			else if (HasProp(line, PREFAB_POS_Y)) axis = (int)AXIS::Y;
			else if (HasProp(line, PREFAB_POS_Z)) axis = (int)AXIS::Z;

			obj.position = ExtractPos(axis);
		}
		else if (HasProp(line, PREFAB_ROT_X) || HasProp(line, PREFAB_ROT_Y) || HasProp(line, PREFAB_ROT_Z))
		{
			int axis = -1;

			if (HasProp(line, PREFAB_ROT_X)) axis = (int)AXIS::X;
			else if (HasProp(line, PREFAB_ROT_Y)) axis = (int)AXIS::Y;
			else if (HasProp(line, PREFAB_ROT_Z)) axis = (int)AXIS::Z;

			obj.rotation = ExtractRotation(axis);
		} 
		else if(HasProp(line, PREFAB_SCALE_X) || HasProp(line, PREFAB_SCALE_Y) || HasProp(line, PREFAB_SCALE_Z))
		{
			int axis = -1;

			if (HasProp(line, PREFAB_SCALE_X)) axis = (int)AXIS::X;
			else if (HasProp(line, PREFAB_SCALE_Y)) axis = (int)AXIS::Y;
			else if (HasProp(line, PREFAB_SCALE_Z)) axis = (int)AXIS::Z;

			obj.scale = ExtractScale(axis);
		}
	}

	objects.push_back(obj);
}

bool SceneLoader::HasProp(std::string line, std::string prop)
{
	return line.find(prop) != std::string::npos;
}

int SceneLoader::ExtractFileID(std::string line)
{
	/*int start = line.find_last_of("{fileID: ") + 1;
	int end = line.find_first_of("}");
	line = line.substr(start, end - start);*/

	return (int)std::stoi(line);
}

std::string SceneLoader::ExtractStringValue(std::string line)
{
	return line.substr(line.find(FIELD_VALUE) + FIELD_VALUE.length());
}

int SceneLoader::ExtractIntValue(std::string line)
{
	return std::stoi(ExtractStringValue(line));
}

float SceneLoader::ExtractFloatValue(std::string line)
{
	return std::stof(ExtractStringValue(line));
}

FLOAT3 SceneLoader::ExtractPos(int first_axis)
{
	if (first_axis == -1)
	{
		std::cout << "Extract position failed: axis enum unset\n";
	}

	FLOAT3 pos = {0};

	string line;
	string other_line;
	int num_axes_set = 0;

	std::getline(scene, other_line);
	switch ((AXIS)first_axis)
	{
	case AXIS::X:
		pos.x = ExtractFloatValue(other_line);
		break;
	case AXIS::Y:
		pos.y = ExtractFloatValue(other_line);
		break;
	case AXIS::Z:
		pos.z = ExtractFloatValue(other_line);
		break;
	}
	num_axes_set++;

	while (num_axes_set < 3)
	{
		std::getline(scene, line);
		if (HasProp(line, PREFAB_POS_X))
		{
			std::getline(scene, other_line);
			pos.x = ExtractFloatValue(other_line);
			num_axes_set++;
		}
		else if (HasProp(line, PREFAB_POS_Y))
		{
			std::getline(scene, other_line);
			pos.y = ExtractFloatValue(other_line);
			num_axes_set++;
		} else if (HasProp(line, PREFAB_POS_Z))
		{
			std::getline(scene, other_line);
			pos.z = ExtractFloatValue(other_line);
			num_axes_set++;
		}
	}

	return pos;
}

FLOAT3 SceneLoader::ExtractRotation(int first_axis)
{
	if (first_axis == -1)
	{
		std::cout << "Extract rotation failed: axis enum unset\n";
	}

	FLOAT3 rot = { 0 };

	string line;
	string other_line;
	int num_axes_set = 0;

	switch ((AXIS)first_axis)
	{
	case AXIS::X:
		std::getline(scene, other_line);
		rot.x = ExtractFloatValue(other_line);
		break;
	case AXIS::Y:
		std::getline(scene, other_line);
		rot.y = ExtractFloatValue(other_line);
		break;
	case AXIS::Z:
		std::getline(scene, other_line);
		rot.z = ExtractFloatValue(other_line);
		break;
	}

	num_axes_set++;

	while (num_axes_set < 3)
	{
		std::getline(scene, line);
		if (HasProp(line, PREFAB_ROT_X))
		{
			std::getline(scene, other_line);
			rot.x = ExtractFloatValue(other_line);
			num_axes_set++;
		}
		else if (HasProp(line, PREFAB_ROT_Y))
		{
			std::getline(scene, other_line);
			rot.y = ExtractFloatValue(other_line);
			num_axes_set++;
		}
		else if (HasProp(line, PREFAB_ROT_Z))
		{
			std::getline(scene, other_line);
			rot.z = ExtractFloatValue(other_line);
			num_axes_set++;
		}
	}

	return rot;
}

FLOAT3 SceneLoader::ExtractScale(int first_axis)
{
	if (first_axis == -1)
	{
		std::cout << "Extract scale failed: axis enum unset\n";
	}

	FLOAT3 scale = { 0 };

	string line;
	string other_line;
	int num_axes_set = 0;

	std::getline(scene, other_line);
	switch (AXIS(first_axis))
	{
	case AXIS::X:
		scale.x = ExtractFloatValue(other_line);
		break;
	case AXIS::Y:
		scale.y = ExtractFloatValue(other_line);
		break;
	case AXIS::Z:
		scale.z = ExtractFloatValue(other_line);
		break;
	}
	num_axes_set++;

	while (num_axes_set < 3)
	{
		std::getline(scene, line);
		if (HasProp(line, PREFAB_SCALE_X))
		{
			std::getline(scene, other_line);
			scale.x = ExtractFloatValue(other_line);
			num_axes_set++;
		}
		else if(HasProp(line, PREFAB_SCALE_Y))
		{
			std::getline(scene, other_line);
			scale.y = ExtractFloatValue(other_line);
			num_axes_set++;
		}
		else if (HasProp(line, PREFAB_SCALE_Z))
		{
			std::getline(scene, other_line);
			scale.z = ExtractFloatValue(other_line);
			num_axes_set++;
		}
	}

	return scale;
}

std::string SceneLoader::GenerateGameObjectString(GameObject& obj)
{
	string out;
	out += "<GameObject>\n";
	out += "#name\n";
	out += string(obj.name) + "\n";
	out += "#position\n";
	out += std::to_string(obj.position.x) + " " + std::to_string(obj.position.y) + " " + std::to_string(obj.position.z) + "\n";
	out += "#rotation\n";
	out += std::to_string(obj.rotation.x) + " " + std::to_string(obj.rotation.y) + " " + std::to_string(obj.rotation.z) + "\n";
	out += "#scale\n";
	out += std::to_string(obj.scale.x) + " " + std::to_string(obj.scale.y) + " " + std::to_string(obj.scale.z) + "\n";
	out += "</GameObject>\n";

	return out;
}