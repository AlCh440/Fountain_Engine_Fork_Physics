#pragma once
#include "Globals.h"
#include <iostream>
#include "GameObject.h"

class GameObject;
class GOC_MeshRenderer;
class GOC_Transform;
class GOC_Texture;
class GOC_Camera;

enum class GOC_Type
{
	GOC_NULL = -4,
	GOC_TRANSFORM = 0,
	GOC_MESH_RENDERER = 1,
	GOC_TEXTURE = 2,
	GOC_CAMERA = 3,
	GOC_PRIMITIVE,
};



class GameObjectComponent
{
public:
	GameObjectComponent()
	{
		id = -1;
		enabled = true;
		GOC_type = GOC_Type::GOC_NULL;
	}

	~GameObjectComponent()
	{
	}

protected:
	int id;
	std::string name;
	bool enabled;
	GameObject* gameObject;
	GOC_Type GOC_type;
public:

	GOC_Type GetGOC_Type() const
	{
		return GOC_type;
	}

	virtual bool Execute() = 0;

	std::string GetName() const
	{
		return name;
	}

	bool IsEnabled() const
	{
		return enabled;
	}

	bool Enable()
	{
		enabled = true;
		return enabled;
	}

	bool Disable()
	{
		enabled = false;
		return enabled;
	}

	GameObject* GetGameObject() const
	{
		return gameObject;
	}

	int GetID() const
	{
		return id;
	}

	virtual bool SaveState(JSON_Value* file, std::string root = "") const { return true; };
	virtual bool LoadState(JSON_Value* file, std::string root = "") { return true; };

};

