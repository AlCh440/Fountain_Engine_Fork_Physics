#pragma once
#include "Module.h"
#include "Globals.h"

class ModuleUI : public Module
{
public:
	ModuleUI(bool start_enabled = true);
	~ModuleUI();

	bool Start();
	update_status PreUpdate(float dt) override;
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;
	bool CleanUp();

	bool closeButton = false;
	bool openAbout = false;

	bool fullScreen = false;
	bool Vsync = false;
	bool resizable = false;

	//TODO 9: Create an "OnCollision" method specific for this module



private:
	
};