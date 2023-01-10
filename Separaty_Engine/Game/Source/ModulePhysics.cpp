#include "Globals.h"
#include "Application.h"
#include "PhysBody.h"
#include "ModulePhysics.h"

#ifdef _DEBUG
#pragma comment (lib, "BulletDynamics_debug.lib")
#pragma comment (lib, "BulletCollision_debug.lib")
#pragma comment (lib, "LinearMath_debug.lib")
#else
#pragma comment (lib, "Bullet/libx86/BulletDynamics.lib")
#pragma comment (lib, "Bullet/libx86/BulletCollision.lib")
#pragma comment (lib, "Bullet/libx86/LinearMath.lib")
#endif

ModulePhysics::ModulePhysics() : Module()
{
	debug = true;

	collision_conf = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collision_conf);
	broad_phase = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver();
	
	debug_draw = new DebugDrawer();
}

// Destructor
ModulePhysics::~ModulePhysics()
{
	delete debug_draw;
	delete solver;
	delete broad_phase;
	delete dispatcher;
	delete collision_conf;
}



// ---------------------------------------------------------
bool ModulePhysics::Start()
{
	world = new btDiscreteDynamicsWorld(dispatcher, broad_phase, solver, collision_conf);
	world->setGravity(btVector3(0, -10, 0));

	world->setDebugDrawer(debug_draw);

	// LETS TRY SETTING SOME GROUND
	btMotionState* motion = new btDefaultMotionState();
	btCollisionShape* shape = new btStaticPlaneShape(btVector3(0, 1, 0), 0);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(0.0f, motion, shape);

	btRigidBody* ground = new btRigidBody(rbInfo);
	world->addRigidBody(ground);

	return true;
}

// ---------------------------------------------------------
update_status ModulePhysics::PreUpdate(float dt)
{
	world->stepSimulation(dt, 15);

	return UPDATE_CONTINUE;
}

// ---------------------------------------------------------
update_status ModulePhysics::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		Prim_Sphere s(1);
		
		//s.SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);
		s.SetPos(0, 10, 0);
		float force = 30.0f;
		AddSphere(s, 0);
	}

	if (debug == true)
	{
		world->debugDrawWorld();
	}


	return UPDATE_CONTINUE;
}

// ---------------------------------------------------------
update_status ModulePhysics::PostUpdate(float dt)
{
	

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModulePhysics::CleanUp()
{
	

	delete world;

	return true;
}

PhysBody* ModulePhysics::AddSphere(const Prim_Sphere& sphere, float mass)
{
	btCollisionShape* colShape = new btSphereShape(sphere.radius);
	shapes.push_back(colShape);

	btTransform startTransform;
	startTransform.setFromOpenGLMatrix(&sphere.transform);

	btVector3 localInertia(0, 0, 0);
	if (mass != 0.f)
		colShape->calculateLocalInertia(mass, localInertia);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	motions.push_back(myMotionState);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);

	btRigidBody* body = new btRigidBody(rbInfo);
	PhysBody* pbody = new PhysBody(body);

	body->setUserPointer(pbody);
	world->addRigidBody(body);
	bodies.push_back(pbody);

	return pbody;
}



// ----------------------------------------------------------------------
void DebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{

	line.origin.Set(from.getX(), from.getY(), from.getZ());
	line.destination.Set(to.getX(), to.getY(), to.getZ());
	line.color.Set(color.getX(), color.getY(), color.getZ());
	line.Render();
}

void DebugDrawer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{

	point.transform.translate(PointOnB.getX(), PointOnB.getY(), PointOnB.getZ());
	point.color.Set(color.getX(), color.getY(), color.getZ());
	point.Render();
}

void DebugDrawer::setDebugMode(int debugMode)
{
	mode = (DebugDrawModes)debugMode;
}

int	 DebugDrawer::getDebugMode() const
{
	return mode;
}
