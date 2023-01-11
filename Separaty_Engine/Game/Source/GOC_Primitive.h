#pragma once

#include "GameObject.h"
#include "Globals.h"
#include <vector>

class GameObjectComponent;
class GameObject;



class GOC_Primitive : public GameObjectComponent
{
public:
	GOC_Primitive(GameObject* gameObjectAttached, Primitive* prim);
	~GOC_Primitive();


	void Render();
	bool Execute();


	bool LoadState(JSON_Value* file, std::string root = "") override;
	bool SaveState(JSON_Value* file, std::string root = "") const override;

	
	
private:
	Primitive* primitive;

};
