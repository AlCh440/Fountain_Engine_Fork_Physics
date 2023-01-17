#pragma once

#include "GameObject.h"
#include "Globals.h"
#include <vector>

class GameObjectComponent;
class GameObject;



class GOC_Primitive : public GameObjectComponent
{
public:
	bool first_prim = true;
	GOC_Primitive(GameObject* gameObjectAttached, Primitive* prim, int id);
	GOC_Primitive(GameObject* gameObjectAttached, int id);
	~GOC_Primitive();


	void Render();
	bool Execute();

	void DeletePrimitive();

	void CreateCubeFromAABB();
	void CreateCube(float mass = 0);
	void CreateSphere(float mass = 0);

	void ChangeMass(float mass);
	bool LoadState(JSON_Value* file, std::string root = "") override;
	bool SaveState(JSON_Value* file, std::string root = "") const override;

	
	Primitive* primitive;
private:
	

};
