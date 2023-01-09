#pragma once

#include <iostream>
#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleSceneIntro.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
//#include "ModulePhysics.h"
#include "ModuleUI.h"
#include "EngineSystem.h"

#include "parson.h"

class EngineSystem;

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleSceneIntro* scene_intro;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModuleUI* ui;
	EngineSystem* engineSystem;
	//ModulePhysics* physics;

	bool debug;
private:

	Timer	ms_timer;
	float	dt;
	std::vector<Module*> list_modules;

	mutable bool saveGameRequested;
	bool loadGameRequested;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

	void RequestBrowser(const char* string);

	void LoadGameRequest();
	bool SaveGameRequest() const;

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();

	bool LoadGame();
	bool SaveGame() const;

};