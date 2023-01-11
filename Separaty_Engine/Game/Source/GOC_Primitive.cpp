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

void GOC_Primitive::CreatePrimitive()
{
	GOC_Transform* comp_transform = (GOC_Transform*)gameObject->GetComponent(GOC_Type::GOC_TRANSFORM);
	GOC_MeshRenderer* comp_mesh = (GOC_MeshRenderer*)gameObject->GetComponent(GOC_Type::GOC_MESH_RENDERER);
	vec pos = comp_mesh->GetMesh().bbox.CenterPoint();
	vec size = comp_mesh->GetMesh().bbox.Size();

	Prim_Cube* cube = new Prim_Cube(size.x, size.y, size.z);
	cube->SetPos(pos.x, pos.y, pos.z);

	App->physics->AddCube(cube, 0);
	
	primitive = cube;
}

void GOC_Primitive::DeletePrimitive()
{
	App->physics->world->removeRigidBody(primitive->phys->body);
	primitive->phys->~PhysBody();
	primitive = NULL;
}

bool GOC_Primitive::LoadState(JSON_Value* file, std::string root)
{
	return true;
}

bool GOC_Primitive::SaveState(JSON_Value* file, std::string root) const
{
	return true;
}
