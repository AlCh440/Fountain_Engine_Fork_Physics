
#include "ModulePhysics.h"
//#include "Globals.h"
//#include "Application.h"
//
//ModulePhysics::ModulePhysics(bool start_enabled) : Module(start_enabled)
//{
//	collision_conf = new btDefaultCollisionConfiguration();
//	dispatcher = new btCollisionDispatcher(collision_conf);
//	broad_phase = new btDbvtBroadphase();
//	solver = new btSequentialImpulseConstraintSolver();
//}
//
//ModulePhysics::~ModulePhysics()
//{
//	// inverse order of creation!!!
//	delete solver;
//	delete broad_phase;
//	delete dispatcher;
//	delete collision_conf;
//}
//
//
//bool ModulePhysics::Start()
//{
//	world = new btDiscreteDynamicsWorld(dispatcher, broad_phase, solver, collision_conf);
//
//	return false;
//}
//
//update_status ModulePhysics::PreUpdate(float dt)
//{
//	return UPDATE_CONTINUE;
//}
//
//update_status ModulePhysics::Update(float dt)
//{
//	return UPDATE_CONTINUE;
//}
//
//update_status ModulePhysics::PostUpdate(float dt)
//{
//	return UPDATE_CONTINUE;
//}
//
//bool ModulePhysics::CleanUp()
//{
//	delete world;
//
//	return false;
//}
//

