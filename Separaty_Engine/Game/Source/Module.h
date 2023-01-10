#pragma once

#include "parson.h"
#include <iostream>

class Module
{
private :
	
	
public:

	std::string name;

	Module(bool start_enabled = true) : enabled(start_enabled)
	{}

	virtual ~Module()
	{}

	virtual bool Init() 
	{
		return true; 
	}

	virtual bool Start()
	{
		return true;
	}

	virtual update_status PreUpdate(float dt)
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status Update(float dt)
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status PostUpdate(float dt)
	{
		return UPDATE_CONTINUE;
	}

	virtual bool CleanUp() 
	{ 
		return true; 
	}

	virtual bool LoadState(JSON_Value* file, std::string root = "")
	{
		return true;
	}

	virtual bool SaveState(JSON_Value* file, std::string root = "") const
	{
		return true;
	}

	bool enabled = true;
	//TODO 7: Create virtual method "On Collision", that recieves the two colliding PhysBodies
};

