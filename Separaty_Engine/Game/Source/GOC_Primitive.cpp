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
	return true;
}

void GOC_Primitive::DeletePrimitive()
{
	App->physics->world->removeRigidBody(primitive->phys->body);
	primitive->phys->~PhysBody();
	primitive = NULL;
}

void GOC_Primitive::CreateCube()
{
	if (primitive != NULL) DeletePrimitive();

	GOC_Transform* comp_transform = (GOC_Transform*)gameObject->GetComponent(GOC_Type::GOC_TRANSFORM);
	GOC_MeshRenderer* comp_mesh = (GOC_MeshRenderer*)gameObject->GetComponent(GOC_Type::GOC_MESH_RENDERER);
	vec3 pos = comp_transform->GetPosition();
	vec size = comp_mesh->GetMesh().bbox.Size();
	float3 rot = gameObject->transform->rotationEulerLocal;
	float c1 = cos(rot.x /2);
	float c2 = cos(rot.y /2);
	float c3 = cos(rot.z /2);
	float s1 = sin(rot.x /2);
	float s2 = sin(rot.y /2);
	float s3 = sin(rot.z /2);

	float w = c1*c2 * c3 - s1*s2 * s3;
	float x = c1*c2 * s3 + s1*s2 * c3;
	float y = s1 * c2 * c3 + c1 * s2 * s3;
	float z = c1 * s2 * c3 - s1 * c2 * s3;
	float angle = 2 * acos(w);
	double norm = x * x + y * y + z * z;
	if (norm < 0.001) { // when all euler angles are zero angle =0 so
		// we can set axis to anything to avoid divide by zero
		x = 1;
		y = z = 0;
	}
	else {
		norm = sqrt(norm);
		x /= norm;
		y /= norm;
		z /= norm;
	}
	//euler
	Prim_Cube* cube = new Prim_Cube(size.x, size.y, size.z);
	cube->SetRotation(angle * RADTODEG, vec3(x, y, z));
	cube->SetPos(pos.x, pos.y + (size.y/2), pos.z);
	

	App->physics->AddCube(cube, 0);
	primitive = cube;
}

void GOC_Primitive::CreateSphere()
{
	if (primitive != NULL) DeletePrimitive();

	GOC_Transform* comp_transform = (GOC_Transform*)gameObject->GetComponent(GOC_Type::GOC_TRANSFORM);
	GOC_MeshRenderer* comp_mesh = (GOC_MeshRenderer*)gameObject->GetComponent(GOC_Type::GOC_MESH_RENDERER);
	vec3 pos = comp_transform->GetPosition();
	vec size = comp_mesh->GetMesh().bbox.Size();

	Prim_Sphere* sphere = new Prim_Sphere(size.x, 0); //THIS IS TEMPORAL, SHOULDN'T BE SIZE.X BUT A REAL DISTANCE IN 3d
	sphere->SetPos(pos.x, pos.y, pos.z);

	App->physics->AddSphere(sphere, 0);
	primitive = sphere;
}

bool GOC_Primitive::LoadState(JSON_Value* file, std::string root)
{
	return true;
}

bool GOC_Primitive::SaveState(JSON_Value* file, std::string root) const
{
	return true;
}
