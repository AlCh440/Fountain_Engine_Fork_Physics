#include "GOC_Primitive.h"

GOC_Primitive::GOC_Primitive(GameObject* gameObjectAttached, Primitive* prim, int id)
{
	this->id = id;

	this->primitive = prim;
	gameObject = gameObjectAttached;
	GOC_type = GOC_Type::GOC_PRIMITIVE;
}

GOC_Primitive::GOC_Primitive(GameObject* gameObjectAttached, int id)
{
	this->id = id;

	
	gameObject = gameObjectAttached;
	GOC_type = GOC_Type::GOC_PRIMITIVE;

	
}

GOC_Primitive::~GOC_Primitive()
{
}

void GOC_Primitive::Render()
{
}

bool GOC_Primitive::Execute()
{
	if (primitive == NULL && first_prim)
	{
		CreateCube(gameObject->mass);
		//CreateCubeFromAABB();
		first_prim = false;
		ChangeMass(gameObject->mass);
	}

	if (primitive != NULL)
	{
		//if (gameObject->mass != -primitive->phys->body->getInvMass())
		//{
		//	ChangeMass(gameObject->mass);
		//}
		GOC_Transform* comp_transform = (GOC_Transform*)gameObject->GetComponent(GOC_Type::GOC_TRANSFORM);
		
		
		btTransform a = primitive->phys->body->getCenterOfMassTransform();
	
		//gameObject->transform->set;
		btVector3 pos = a.getOrigin();
		gameObject->transform->SetPos(pos.x(), pos.y(), pos.z());
		gameObject->transform->ApplyTransformations();
		//comp_transform->SetPos(pos.x, pos.y, pos.z);
		
		//comp_transform->ApplyTransformationsWorld();
		//gameObject->transform->SetPos(pos.x, pos.y, pos.z);
		//gameObject->transform->SetRotation(axis, vec3(rot.x, rot.y, rot.z));


	}
	return true;
}

void GOC_Primitive::DeletePrimitive()
{
	if (primitive->phys != NULL)
	{
		App->physics->world->removeRigidBody(primitive->phys->body);
		primitive->phys->~PhysBody();
		primitive = NULL;
	}
}

void GOC_Primitive::CreateCubeFromAABB()
{
	GOC_MeshRenderer* comp_mesh = (GOC_MeshRenderer*)gameObject->GetComponent(GOC_Type::GOC_MESH_RENDERER);

	AABB bbox = comp_mesh->GetMesh().bbox;

	float3 size = bbox.Size().xyz();
	float3 centerPos = bbox.CenterPoint();
	vec3 pos = gameObject->transform->GetPosition();
	float3 rot = gameObject->transform->rotationEulerLocal;
	vec p1 = bbox.CornerPoint(0);
	vec p2 = bbox.CornerPoint(0);
	vec aux(0, 0, 0);
	for (int i = 0; i < 7; i++)
	{
		aux = bbox.CornerPoint(i);
		
		if (aux.x >= p1.x && aux.y >= p1.y && aux.z >= p1.z)
		{
			p1 = aux;
		}

		if (aux.x <= p2.x && aux.y <= p2.y && aux.z <= p2.z)
		{
			p2 = aux;
		}
	}
	Prim_Cube* cube = new Prim_Cube(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
	App->physics->AddCube(cube, 0);
	

	cube->SetPos(pos.x + centerPos.x, pos.y + centerPos.y, pos.z + centerPos.z);
	primitive = cube;
	
	
	//float   c1 = cos(rot.y / 2);
	//float	s1 = sin(rot.y / 2);
	//float	c2 = cos(rot.z / 2);
	//float	s2 = sin(rot.z / 2);
	//float	c3 = cos(rot.x / 2);
	//float	s3 = sin(rot.x / 2);
	//float	c1c2 = c1 * c2;
	//float	s1s2 = s1 * s2;
	//float	w = c1c2 * c3 - s1s2 * s3;
	//float	x = c1c2 * s3 + s1s2 * c3;
	//float	y = s1 * c2 * c3 + c1 * s2 * s3;
	//float	z = c1 * s2 * c3 - s1 * c2 * s3;
	//float	angle = 2 * acos(w);
	//
	//float norm = x * x + y * y + z * z;
	//if (norm < 0.001)
	//{
	//	x = 1;
	//	y = 0;
	//	z = 0;
	//}
	//else
	//{
	//	norm = sqrt(norm);
	//	x /= norm;
	//	y /= norm;
	//	z /= norm;
	//}
	//
	//Prim_Cube* cube = new Prim_Cube(size.x, size.y, size.z);
	//Prim_Cube()
	//App->physics->AddCube(cube, 0);
	//cube->SetRotation(angle * RADTODEG, vec3(x, y, z));
	//cube->SetPos(pos.x + centerPos.x, pos.y + centerPos.y, pos.z + centerPos.z);
	//primitive = cube;
}

void GOC_Primitive::CreateCube(float mass)
{
	if (primitive != NULL) DeletePrimitive();

	GOC_Transform* comp_transform = (GOC_Transform*)gameObject->GetComponent(GOC_Type::GOC_TRANSFORM);
	GOC_MeshRenderer* comp_mesh = (GOC_MeshRenderer*)gameObject->GetComponent(GOC_Type::GOC_MESH_RENDERER);
	float3 centerPos = comp_mesh->GetMesh().bbox.CenterPoint();
	vec3 pos = gameObject->transform->GetPosition();//comp_transform->GetPosition();
	vec size = comp_mesh->GetMesh().bbox.Size();
	float3 rot = gameObject->transform->rotationEulerLocal;


	Quat rotatorQuat = Quat::FromEulerXYZ(rot.x, rot.y, rot.z);
	float angle;
	float4 axis;
	rotatorQuat.ToAxisAngle(axis, angle);
	
	Prim_Cube* cube = new Prim_Cube(size.x, size.y, size.z);
	
	

	App->physics->AddCube(cube, mass);
	cube->SetRotation(angle * RADTODEG, vec3(axis.x, axis.y, axis.z));
	cube->SetPos(pos.x, pos.y, pos.z);
	//cube->SetPos(pos.x + centerPos.x, pos.y + centerPos.y, pos.z + centerPos.z);
	primitive = cube;
}

void GOC_Primitive::CreateSphere(float mass)
{
	if (primitive != NULL) DeletePrimitive();

	GOC_Transform* comp_transform = (GOC_Transform*)gameObject->GetComponent(GOC_Type::GOC_TRANSFORM);
	GOC_MeshRenderer* comp_mesh = (GOC_MeshRenderer*)gameObject->GetComponent(GOC_Type::GOC_MESH_RENDERER);
	vec3 pos = comp_transform->GetPosition();
	vec size = comp_mesh->GetMesh().bbox.Size();

	Prim_Sphere* sphere = new Prim_Sphere(size.x, mass); //THIS IS TEMPORAL, SHOULDN'T BE SIZE.X BUT A REAL DISTANCE IN 3d
	App->physics->AddSphere(sphere, mass);
	sphere->SetPos(pos.x, pos.y, pos.z);
	primitive = sphere;
}

void GOC_Primitive::ChangeMass(float mass)
{
	App->physics->world->removeRigidBody(primitive->phys->body);
	App->physics->AddBody(primitive, primitive->GetType(), mass);
	gameObject->mass = mass;
}

bool GOC_Primitive::LoadState(JSON_Value* file, std::string root)
{
	return true;
}

bool GOC_Primitive::SaveState(JSON_Value* file, std::string root) const
{
	return true;
}
