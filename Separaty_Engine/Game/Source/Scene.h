#pragma once

#include "Globals.h"
#include "Module.h"
#include "GameObject.h"


class EngineSystem;
class GameObject;
class ModuleVehicle;
class GOC_MeshRenderer;

class Scene : public Module
{
public:
	Scene(EngineSystem *system, bool active = true);

	Scene(std::string name, uint id, EngineSystem* system, bool active = true);

	~Scene();

	bool Init();
	bool Start();
	update_status Update(float dt) override;
	bool CleanUp();
	bool LoadState(JSON_Value* file, std::string root = "") override;
	bool SaveState(JSON_Value* file, std::string root = "") const override;
	
	GameObject* CreateNewGameObject();
	ModuleVehicle* CreateNewGameObjectVechicle();

	std::vector<GameObject*> GetGameObjectList() const
	{
		return gameObjects;
	}


	GameObject* GetSelectedGameObject();
	
	void EraseGameObjectFromList(GameObject* gameObject);

	std::vector<GameObject*> gameObjects;
	uint sceneID;
private:

	std::string sceneName;
	bool active;
	EngineSystem * engineSystem;

	vec3 X, Y, Z;

	bool loadedBasics = false;
};

