#pragma once

// Warning disabled ---
#pragma warning( disable : 4577 ) // Warning that exceptions are disabled
#pragma warning( disable : 4530 ) // Warning that exceptions are disabled

#include <windows.h>
#include <stdio.h>
#include "Log.h"

// Configuration -----------
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 1024
#define SCREEN_SIZE 1
#define WIN_FULLSCREEN false
#define WIN_RESIZABLE true
#define WIN_BORDERLESS false
#define WIN_FULLSCREEN_DESKTOP false
#define VSYNC true
#define TITLE "Fountain Engine"
#define ORGANITZATION "UPC CITM"
#define PATH_MODELS "Output/Assets/Project_1/Assets/Models"
#define PATH_SHADERS "Source/Shaders"


#define CAP(n) ((n <= 0.0f) ? n=0.0f : (n >= 1.0f) ? n=1.0f : n=n)

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#define HAVE_M_PI


#define MESH_FILE_EXTENSION ".rmq"
#define TEXTURE_FILE_EXTENSION ".rsm"

typedef unsigned int uint;
typedef unsigned char uchar;
enum CollisionObject
{
	NONE = 1,
	CAR,
	WALL,
	
};

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

enum RoadTypes
{
	
	BOTTOM_RIGHT_CORNER,
	BOTTOM_LEFT_CORNER
};




class Application;
//I hope no one notices this... Brandon?
//I noticed :) but dont worry
extern Application* App;