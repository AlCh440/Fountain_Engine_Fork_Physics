#pragma once
#include "Module.h"
#include "Globals.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"
#include "imgui_internal.h"

#include "UIFunctions.h"

class ModuleUI : public Module
{
public:
	ModuleUI(bool start_enabled = true);
	~ModuleUI();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt) override;
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;
	bool CleanUp();
	bool LoadState(JSON_Value* file, std::string root = "") override;
	bool SaveState(JSON_Value* file, std::string root = "") const override;


	bool closeButton = false;
	bool openAbout = false;

	bool showApplicationData = false;
	bool showPreferences = false;

	bool hierarchy = true;
	bool inspector = true;
	bool assets = true;
	bool showOutput = true;
	bool playStop = true;

	std::vector<char*> outputList;
	float screenX;
	float screenY;

	//PRIMITIVEs

	bool createHouse = false;
	bool createGyarados = false;
	bool createJolteon = false;
	bool createCar_1 = false;


	bool createEmptyObject = false;
	bool createCube = false;
	bool createSphere = false;
	bool createCapsule = false;
	bool createCylinder = false;
	bool createPyramid = false;
	bool createCone = false;
	bool createPlane = false;

	Prim_Cube* object2;
	Prim_Cube* object1;

	PhysBody* decorBody2;
	PhysBody* decorBody;


	bool cleanPrimitives = false;

	void AppendToOutput(char* DEBUG_LOG)
	{
		char* text = new char[4096];
		strncpy_s(text, 4096, DEBUG_LOG, strlen(DEBUG_LOG));

		std::vector<char*>::iterator firstPlace = outputList.begin();
		outputList.insert(firstPlace, text);
	}

	void PrintOutputList()
	{
		for (size_t i = 0; i < outputList.size(); i++)
		{
			ImGui::Text(outputList[i]);
		}

	}

	char inputs[20];
	/*GameObject* gameObject;*/

	//TODO 9: Create an "OnCollision" method specific for this module

	UIFunctions* uiFunctions;

private:
	
};
