#pragma once
#include "Globals.h"
#include "Module.h"

#include <iostream>
#include "Application.h"
#include "GameObjComponent.h"
#include "GOC_MeshRenderer.h"
#include "GOC_Transform.h"
#include "GOC_Texture.h"

#include "p2Point.h"
#include "PhysVehicle3D.h"
#include "GameObject.h"

class EngineSystem;
enum class GOC_Type;
//class GameObjectComponent;
class GOC_MeshRenderer;
class GOC_Transform;
//class GOC_Texture;


#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 1000.0f

struct WindowGameObjectInfo
{
	int selectedGameObjectID = -1;
};

class GameObject : public Module
{
public:
	GameObject(uint id, EngineSystem* system, bool start_enabled = true);
	~GameObject();

	bool Init();
	bool Start();
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;
	bool CleanUp(); 
	bool LoadState(JSON_Value* file, std::string root = "") override;
	bool SaveState(JSON_Value* file, std::string root = "") const override;

	uint GetID() const
	{
		return id;
	}

	GameObject* CreateChildren();
	

	std::vector<GameObject*> GetChildren() const
	{
		return children;
	}

	void Delete();


	std::string GetName()
	{
		return name;
	}

	void ChangeName(std::string changeName) 
	{
		this->name = changeName;
	}

	std::vector<GameObjectComponent*> GetComponents() const
	{
		return components;
	}

	void AddComponent(GOC_Type type);
	GameObjectComponent* GetComponent(GOC_Type type);
	bool selected = false;

	void AttachChild(GameObject* child);
	void RemoveChild(GameObject* child);

	void CopyFromGameObject(GameObject gameobject);
	GOC_Transform* transform;
	WindowGameObjectInfo windowGameObjectInfo = {};
	uint id;
	GameObject* parent = nullptr;
	std::vector<GameObject*> children;
	std::string name;

	bool pendingToDelete = false;

	EngineSystem* engineSystem;
	std::vector<GameObjectComponent*> components;
private:

	

};

class ModuleVehicle : public GameObject
{
public:
	ModuleVehicle(Application* app, bool start_enabled = true);
	ModuleVehicle(uint id, EngineSystem* system, bool start_enabled = true);
	virtual ~ModuleVehicle();

	bool StartVehicle();
	update_status Update(float dt);
	bool CleanUp();
	//void RestartPlayer(int x, int y, int z);
	void OnCollision(PhysBody* body1, PhysBody* body2);

public:
	VehicleInfo car;
	PhysVehicle* vehicle;
	//Sphere* decor;
	//PhysBody3D* decorBody;
	float turn;
	float acceleration;
	float brake;
	float liftForce;
	bool alive;

	bool  following_camera;



	float drag;
	float lift;
	float friction;
};
