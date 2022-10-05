#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"

#include "Log.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"
#include "imgui_internal.h"

ModuleWindow::ModuleWindow(bool start_enabled) : Module(start_enabled)
{
	window = NULL;
	screen_surface = NULL;
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	DEBUG_LOG("Init SDL window & surface");
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		DEBUG_LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		int width = SCREEN_WIDTH * SCREEN_SIZE;
		int height = SCREEN_HEIGHT * SCREEN_SIZE;
		Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;

		//Use OpenGL 2.1
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		if(WIN_FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		if(WIN_RESIZABLE == true)
		{
			flags |= SDL_WINDOW_RESIZABLE;
		}

		if(WIN_BORDERLESS == true)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		if(WIN_FULLSCREEN_DESKTOP == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if(window == NULL)
		{
			DEBUG_LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	DEBUG_LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

void ModuleWindow::SetTitle(const char* title)
{
	SDL_SetWindowTitle(window, title);
}

void ModuleWindow::SetFullscreen(bool fullscreen)
{
	if (fullScreen)	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	if (fullDesktop)	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	else if (fullScreen == false && fullDesktop == false ) SDL_SetWindowFullscreen(window, 0);
}
void ModuleWindow::SetVsync(bool vsync)
{
	vsync = SDL_HINT_RENDER_VSYNC;
}
void ModuleWindow::SetResizable(bool resizable)
{
	SDL_SetWindowResizable(window, resizable);
}
void ModuleWindow::UpdateBrightness()
{
	SDL_SetWindowBrightness(window, brightness);

	DEBUG_LOG("%f");
}

void ModuleWindow::SetWindowSize()
{
	SDL_SetWindowSize(window, width, height);
}

///////


// Width

//Height


////////

void ModuleWindow::FPSGraph(float dt, int size)
{
	fpsLog.push_back(1 / dt);
	sprintf_s(title, 20, "Framerate %.1f", fpsLog[fpsLog.size() - 1]);
	ImGui::PlotHistogram("##framerate", &fpsLog[0], fpsLog.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
	if (fpsLog.size() > size)
	{
		fpsLog.erase(fpsLog.begin());
	}
}

void ModuleWindow::MSGraph(float dt, int size)
{
	msLog.push_back(dt * 1000);
	sprintf_s(title, 20, "Milliseconds %0.1f", msLog[msLog.size() - 1]);
	ImGui::PlotHistogram("##milliseconds", &msLog[0], msLog.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));
	if (msLog.size() > size)
	{
		msLog.erase(msLog.begin());
	}
}

