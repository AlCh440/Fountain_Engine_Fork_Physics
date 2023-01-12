#pragma once
#include "Module.h"
#include "Globals.h"
#include "Primitive.h"

#include "Bullet/include/btBulletDynamicsCommon.h"

// Recommended scale is 1.0f == 1 meter, no less than 0.2 objects
#define GRAVITY btVector3(0.0f, -10.0f, 0.0f) 

class DebugDrawer;
struct PhysBody;
struct PhysVehicle3D;
struct VehicleInfo;

class ModulePhysics : public Module
{
public:
	ModulePhysics();
	~ModulePhysics();


	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	PhysBody* AddBody(Primitive* prim, PrimitiveTypes primType, float mass);
	PhysBody* AddSphere(Prim_Sphere* sphere, float mass = 1.0f);
	PhysBody* AddCube(Prim_Cube* cube, float mass = 1.0f);

	btDiscreteDynamicsWorld* world;

private:

	std::vector<PhysBody*> bodies;
	std::vector<btCollisionShape*> shapes;
	std::vector<btDefaultMotionState*> motions;

	bool debug;

	btDefaultCollisionConfiguration* collision_conf;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* broad_phase;
	btSequentialImpulseConstraintSolver* solver;

	btDefaultVehicleRaycaster* vehicle_raycaster;
	DebugDrawer* debug_draw;

	
};

class DebugDrawer : public btIDebugDraw
{
public:
	DebugDrawer() : line(0, 0, 0)
	{}

	void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
	void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);
	void reportErrorWarning(const char* warningString) {};
	void draw3dText(const btVector3& location, const char* textString) {};
	void setDebugMode(int debugMode);
	int	 getDebugMode() const;

	DebugDrawModes mode = DBG_DrawWireframe;
	Prim_Line line;
	Primitive point;
};
