#include "GOC_Transform.h"



GOC_Transform::GOC_Transform(GameObject* gameObjectAttached, int id)
{
	this->id = id;
	transformWorld = IdentityMatrix;
	transformLocal = IdentityMatrix;
	GOC_type = GOC_Type::GOC_TRANSFORM;
	gameObject = gameObjectAttached;
}

GOC_Transform::~GOC_Transform()
{
}

void GOC_Transform::SetPos(float x, float y, float z)
{
	transformWorld.translate(x, y, z);
}


// ------------------------------------------------------------
void GOC_Transform::SetRotation(float angle, const vec3& u)
{
	transformWorld.rotate(angle, u);
}

// ------------------------------------------------------------
void GOC_Transform::SetScale(float x, float y, float z)
{
	transformWorld.scale(x, y, z);
}

bool GOC_Transform::Execute()
{	

	return true;
}

void GOC_Transform::ApplyTransformations()
{

	translationWorld = translationLocal;
	rotationWorld = rotationLocal;
	scalingWorld = scalingLocal;
	if (gameObject->parent != nullptr)
	{
		//12 13 14
		translationWorld = AddMatrices(gameObject->parent->transform->translationWorld, translationLocal);
		translationWorld.M[0] = translationWorld.M[5] = translationWorld.M[10] = translationWorld.M[15] = 1;
		rotationWorld = gameObject->parent->transform->rotationWorld * rotationLocal;
		scalingWorld = gameObject->parent->transform->scalingWorld * scalingLocal;
	}

	ApplyTransformationsWorld();
}

void GOC_Transform::ApplyTransformationsWorld()
{
	transformWorld =  translationWorld * rotationWorld * scalingWorld;


	for (GameObject* go : gameObject->GetChildren())
	{
		go->transform->ApplyTransformations();
	}

}



bool GOC_Transform::SaveState(JSON_Value* file, std::string root) const
{
	json_object_dotset_number(json_object(file), std::string(root + "transform.position.x").c_str(), (double)gameObject->transform->translationLocal.translation().x);
	json_object_dotset_number(json_object(file), std::string(root + "transform.position.y").c_str(), (double)gameObject->transform->translationLocal.translation().y);
	json_object_dotset_number(json_object(file), std::string(root + "transform.position.z").c_str(), (double)gameObject->transform->translationLocal.translation().z);

	json_object_dotset_number(json_object(file), std::string(root + "transform.rotationRad.x").c_str(), (double)gameObject->transform->rotationEulerLocal.x);
	json_object_dotset_number(json_object(file), std::string(root + "transform.rotationRad.y").c_str(), (double)gameObject->transform->rotationEulerLocal.y);
	json_object_dotset_number(json_object(file), std::string(root + "transform.rotationRad.z").c_str(), (double)gameObject->transform->rotationEulerLocal.z);


	json_object_dotset_number(json_object(file), std::string(root + "transform.scale.x").c_str(), (double)gameObject->transform->scalingLocal.scaling().x);
	json_object_dotset_number(json_object(file), std::string(root + "transform.scale.y").c_str(), (double)gameObject->transform->scalingLocal.scaling().y);
	json_object_dotset_number(json_object(file), std::string(root + "transform.scale.z").c_str(), (double)gameObject->transform->scalingLocal.scaling().z);
	return true;
}

bool GOC_Transform::LoadState(JSON_Value* file, std::string root)
{



	return true;
}
