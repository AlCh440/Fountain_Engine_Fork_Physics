#pragma once
#include "Module.h"
#include "Globals.h"
#include "Primitive.h"

class Primitive;
class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;
	bool CleanUp();
	bool LoadState(JSON_Value* file, std::string root = "") override;
	bool SaveState(JSON_Value* file, std::string root = "") const override;

	//Draw 

	Prim_Plane plane;
	Prim_Cube cube;
	Prim_Sphere sphere;
	Prim_Cylinder cil;

private:
	std::vector<Primitive*> primitives;
};
