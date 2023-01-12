#include "Globals.h"
#include "Application.h"
#include "PhysBody.h"
#include "ModulePhysics.h"
#include "Bullet/include/LinearMath/btIDebugDraw.h"

#ifdef _DEBUG
#pragma comment (lib, "BulletDynamics_debug.lib")
#pragma comment (lib, "BulletCollision_debug.lib")
#pragma comment (lib, "LinearMath_debug.lib")
#else
#pragma comment (lib, "Bullet/libx86/BulletDynamics.lib")
#pragma comment (lib, "Bullet/libx86/BulletCollision.lib")
#pragma comment (lib, "Bullet/libx86/LinearMath.lib")
#endif

enum	DebugDrawModes
{
	DBG_NoDebug = 0,
	DBG_DrawWireframe = 1,
	DBG_DrawAabb = 2,
	DBG_DrawFeaturesText = 4,
	DBG_DrawContactPoints = 8,
	DBG_NoDeactivation = 16,
	DBG_NoHelpText = 32,
	DBG_DrawText = 64,
	DBG_ProfileTimings = 128,
	DBG_EnableSatComparison = 256,
	DBG_DisableBulletLCP = 512,
	DBG_EnableCCD = 1024,
	DBG_DrawConstraints = (1 << 11),
	DBG_DrawConstraintLimits = (1 << 12),
	DBG_FastWireframe = (1 << 13),
	DBG_DrawNormals = (1 << 14),
	DBG_DrawFrames = (1 << 15),
	DBG_MAX_DEBUG_DRAW_MODE
};

ModulePhysics::ModulePhysics() : Module()
{
	debug = true;

	collision_conf = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collision_conf);
	broad_phase = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver();
	

	debug_draw = new DebugDrawer();

	world = new btDiscreteDynamicsWorld(dispatcher, broad_phase, solver, collision_conf);
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
	
	world->setDebugDrawer(debug_draw);
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
		
		s.SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);
		float force = 60.0f;
		AddSphere(&s, 1)->Push(-(App->camera->Z.x * force), -(App->camera->Z.y * force), -(App->camera->Z.z * force));;
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

PhysBody* ModulePhysics::AddBody(Primitive* prim, PrimitiveTypes primType, float mass)
{
	switch (primType)
	{
	case Primitive_Point:
		break;
	case Primitive_Line:
		break;
	case Primitive_Plane:
		break;
	case Primitive_Cube:
		return AddCube((Prim_Cube*)prim, mass);
		break;
	case Primitive_Sphere:
		return AddSphere((Prim_Sphere*)prim, mass);
		break;
	case Primitive_Cylinder:
		break;
	default:
		return NULL;
		break;
	}
}

PhysBody* ModulePhysics::AddSphere(Prim_Sphere* sphere, float mass)
{
	btCollisionShape* colShape = new btSphereShape(sphere->radius);
	shapes.push_back(colShape);

	btTransform startTransform;
	startTransform.setFromOpenGLMatrix(&sphere->transform);

	btVector3 localInertia(0, 0, 0);
	if (mass != 0.f)
		colShape->calculateLocalInertia(mass, localInertia);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	motions.push_back(myMotionState);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);

	btRigidBody* body = new btRigidBody(rbInfo);
	PhysBody* pbody = new PhysBody(body);

	sphere->phys = pbody;
	body->setUserPointer(pbody);
	world->addRigidBody(body);
	bodies.push_back(pbody);

	return pbody;
}

PhysBody* ModulePhysics::AddCube(Prim_Cube* cube, float mass)
{
	btCollisionShape* colShape = new btBoxShape(btVector3(cube->size.x * 0.5f, cube->size.y * 0.5f, cube->size.z * 0.5f));
	shapes.push_back(colShape);

	btTransform startTransform;
	startTransform.setFromOpenGLMatrix(&cube->transform);

	btVector3 localInertia(0, 0, 0);
	if (mass != 0.f)
		colShape->calculateLocalInertia(mass, localInertia);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	motions.push_back(myMotionState);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);

	btRigidBody* body = new btRigidBody(rbInfo);
	PhysBody* pbody = new PhysBody(body);

	cube->phys = pbody;
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
