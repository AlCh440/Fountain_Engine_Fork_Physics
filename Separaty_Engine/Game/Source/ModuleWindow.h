#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "Globals.h"
#include "SDL/include/SDL.h"

#include <vector>

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow(bool start_enabled = true);

	// Destructor
	virtual ~ModuleWindow();

	bool Init();
	bool CleanUp();

	void SetTitle(const char* title);

	//Windows
	void SetFullscreen(bool fullscreen);
	void SetVsync(bool vsync);
	void SetResizable(bool resizable);
	void UpdateBrightness();
	void UpdateWindowSize();

	float brightness = 1.0f;
	int width = 1280;
	int height = 1024;

	bool fullScreen = false;
	bool vsync = false;
	bool resizable = true;
	bool fullDesktop = false;
	
	//FPS / MS
	std::vector<float> fpsLog;
	std::vector<float> msLog;

	void FPSGraph(float dt, int size);
	void MSGraph(float dt, int size);

	int maxFPS = 60;
	char title[20];

public:
	//The window we'll be rendering to
	SDL_Window* window;

	//The surface contained by the window
	SDL_Surface* screen_surface;
};

#endif // __ModuleWindow_H__