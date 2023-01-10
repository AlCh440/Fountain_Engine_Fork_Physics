#pragma once
//#include "Module.h"
#include "Globals.h"
#include "Module.h"
#include <../../Module.h>
#include "Bullet/include/btBulletDynamicsCommon.h"


class ModulePhysics : public Module
{
public:
	ModulePhysics();
	~ModulePhysics();

	bool Start();
	update_status PreUpdate(float dt) override;
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;
	bool CleanUp();

private:

	//we'll need that in the future :)
	//bool debug;

	btDefaultCollisionConfiguration* collision_conf;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* broad_phase;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* world;

};

