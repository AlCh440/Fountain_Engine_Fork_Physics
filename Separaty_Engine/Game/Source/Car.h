#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "PhysVehicle3D.h"

#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 1000.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	//void RestartPlayer(int x, int y, int z);
	void OnCollision(PhysBody* body1, PhysBody* body2);

public:
	VehicleInfo car;
	PhysVehicle3D* vehicle;
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
