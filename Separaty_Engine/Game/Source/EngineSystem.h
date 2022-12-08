#pragma once

#include "Globals.h"
#include "Module.h"

#include "Scene.h"
#include "GameObject.h"
#include "GameObjComponent.h"
#include "Mesh.h"
#include "Model.h"
#include "Shader.h"
#include "TextureLoader.h"

#include <Assimp/include/Importer.hpp>
#include <Assimp/include/scene.h>


class Scene;
class Mesh;
class Model;
class Shader;


class EngineSystem : public Module
{
public:
	EngineSystem();
	~EngineSystem();

	bool Start();
	bool Init();
	update_status PreUpdate(float dt) override;
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;
	bool CleanUp();

	bool LoadScene();
	Scene* CreateNewScene();

	std::vector<Scene*> GetSceneList() const
	{
		return scenes;
	}



	Scene* GetCurrentScene() const;


	bool LoadState(JSON_Value* file) override;
	bool SaveState(JSON_Value* file) const override;

	bool Save();

	GameObject* CreateNewGameObject();
	GameObjectComponent* CreateNewGOC(GameObject* goAttached, GOC_Type type);

	bool LoadFromPath(char* draggedFileDir,bool createGameobject = true);

	std::vector<Mesh> GetAllMeshes() const
	{
		return allMeshes;
	}

	std::vector<Texture> GetAllTextures() const
	{
		return allTextures;
	}

	std::vector<GameObject*> GetAllGameObjects() const
	{
		return allGameObjects;
	}

	std::vector<GameObjectComponent*> GetAllGameObjectComponents() const
	{
		return allGameObjectComponents;
	}

	Assimp::Importer importer;

	void AddToGameObjectsSelected(GameObject* toAdd)
	{
		selectedGameObjects.push_back(toAdd);
	}

	std::vector<GameObject*> GetselectedGameObjects() const
	{
		return selectedGameObjects;
	}


private:
	
	bool LoadModel(char* path, std::string extension ,bool createGameobject = true);


	int scenes_id = 0;

	std::vector<Scene*> scenes;
	std::vector<GameObject*> allGameObjects;
	std::vector<GameObjectComponent*> allGameObjectComponents;
	std::vector<Model*> allModels; //delete
	std::vector<Mesh> allMeshes;
	std::vector<Texture> allTextures;

	std::vector<std::string> modelExtensionsAccepted;
	std::vector<std::string> imageExtensionsAccepted;

	Scene* currentScene;

	std::vector<GameObject*> selectedGameObjects;

};

