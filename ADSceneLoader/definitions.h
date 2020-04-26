#pragma once

#include <string>

using std::string;

// Cpp helper defs

// Enums
enum class AXIS
{
	X = 0,
	Y = 1,
	Z = 2,
};

// Headers
string HEADER_GAME_OBJECT = "--- !u!";
string OT_GAME_OBJECT = "GameObject:";

// Props
string FIELD_VALUE = "value: ";

string OT_PREFAB_INST = "PrefabInstance:";
string PREFAB_NAME = "propertyPath: m_Name";
string PREFAB_POS_X = "propertyPath: m_LocalPosition.x";
string PREFAB_POS_Y = "propertyPath: m_LocalPosition.y";
string PREFAB_POS_Z = "propertyPath: m_LocalPosition.z";
string PREFAB_ROT_X = "m_LocalRotation.x";
string PREFAB_ROT_Y = "m_LocalRotation.y";
string PREFAB_ROT_Z = "m_LocalRotation.z";
string PREFAB_SCALE_X = "propertyPath: m_LocalScale.x";
string PREFAB_SCALE_Y = "propertyPath: m_LocalScale.y";
string PREFAB_SCALE_Z = "propertyPath: m_LocalScale.z";
string END_PREFAB_INST = "m_SourcePrefab:";