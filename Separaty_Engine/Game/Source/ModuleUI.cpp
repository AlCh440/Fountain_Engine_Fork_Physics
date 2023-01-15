#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "UIFunctions.h"
#include "Car.h"


#include <string> 

#include "Glew/include/GL/glew.h"

#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

//#include "opengl_shaders.h"

ModuleUI::ModuleUI(bool start_enabled) : Module(start_enabled)
{
	name = "User_Interface";

}

ModuleUI::~ModuleUI()
{}


bool ModuleUI::Init()
{

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;


	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; 
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;


	ImGuiStyle& style = ImGui::GetStyle();

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
	ImGui_ImplOpenGL3_Init();

	/*gameObject = new GameObject();
	gameObject->Init();
	gameObject->Start();*/

	uiFunctions = new UIFunctions();

	return true;
}

bool ModuleUI::Start()
{
	uiFunctions->Start();

	return true;
}

update_status ModuleUI::PreUpdate(float dt)
{
	

	return UPDATE_CONTINUE;
}


// Update
update_status ModuleUI::Update(float dt)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	/*ImGui::ShowDemoWindow();
	ImGui::Begin("Separaty Engine");
	ImGui::SetWindowSize({ 400, 400 }, 0);*/

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	screenX = io.DisplaySize.x;
	screenY = io.DisplaySize.y;

	/*if (ImGui::Button("Example2", { 250, 150 }))
	{
		exit(0);
	}*/

	/////////////////////
	if (ImGui::BeginMainMenuBar())
	{
		//FILE 
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New Scene" , "CTRL + N"))
			{

			}
			if (ImGui::MenuItem("Open Scene", "CTRL + O", false, false))
			{

			}
			ImGui::Separator();
			if (ImGui::MenuItem("Save", "CTRL + S"))
			{

				App->SaveGameRequest();
			}
			if (ImGui::MenuItem("Save As", "CTRL + SHIFT + S", false, false))
			{

			}
			if (ImGui::MenuItem("Load", "CTRL + L"))
			{
				App->LoadGameRequest();
			}
			ImGui::Separator();
			if (ImGui::MenuItem("New Project","", false, false))
			{

			}
			if (ImGui::MenuItem("Open Project", "", false, false))
			{

			}
			if (ImGui::MenuItem("Save Project", "", false, false))
			{

			}
			ImGui::Separator();
			if (ImGui::MenuItem("Exit"))
			{
				return UPDATE_STOP;
			}
			ImGui::EndMenu();
		}


		// EDIT
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL + Z", false, false))
			{

			}
			if (ImGui::MenuItem("Redo", "CTRL + Y", false, false))
			{

			}
			ImGui::Separator();
			if (ImGui::MenuItem("Select All", "SHIFT + A", false, false))
			{

			}
			if (ImGui::MenuItem("Deselect All", "SHIFT + D", false, false))
			{

			}
			/*if (ImGui::MenuItem("Invert Selection", "CTRL + I"))
			{

			}*/
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL + X", false, false))
			{

			}
			if (ImGui::MenuItem("Copy", "CTRL + C", false, false))
			{

			}
			if (ImGui::MenuItem("Paste", "CTRL + V", false, false))
			{

			}
			ImGui::Separator();
			if (ImGui::MenuItem("Duplicate", "CTRL + D", false, false))
			{

			}
			if (ImGui::MenuItem("Rename", "SHIFT + R", false, false))
			{

			}
			if (ImGui::MenuItem("Delete", "SUPR", false, false))
			{

			}
			ImGui::Separator();
			if (ImGui::MenuItem("Frame Selected", "F", false, false))
			{

			}
			if (ImGui::MenuItem("Lock View to Selected", "SHIFT + F", false, false))
			{

			}
			ImGui::Separator();
			if (ImGui::MenuItem("Project Settings...","", false, false))
			{

			}
			if (ImGui::MenuItem("Preferences..."))
			{
				showPreferences = !showPreferences;
				
			}
			if (ImGui::MenuItem("Show Application Data"))
			{
				showApplicationData = !showApplicationData;
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Controls", "", false, false))
			{

			}
			ImGui::EndMenu();
		}

		//Game Object
		if (ImGui::BeginMenu("Game Object"))
		{
			if (ImGui::MenuItem("Create Empty"))
			{
				createEmptyObject = true;
			}
			ImGui::Separator();
			if (ImGui::TreeNode("Create Primitives"))
			{
				if (ImGui::MenuItem("Cube"))
				{
					createCube = true;
				}
				if (ImGui::MenuItem("Sphere"))
				{
					createSphere = true;
				}
				if (ImGui::MenuItem("Capsule"))
				{
					createCapsule = true;
				}
				if (ImGui::MenuItem("Cylinder"))
				{
					createCylinder = true;
				}
				if (ImGui::MenuItem("Pyramid"))
				{
					createPyramid = true;
				}
				if (ImGui::MenuItem("Cone"))
				{
					createCone = true;
				}
				if (ImGui::MenuItem("Plane"))
				{
					createPlane = true;
				}
				ImGui::Separator();
				if (ImGui::MenuItem("Clean Primitives", "", false, false))
				{
					cleanPrimitives = true;
				}
				ImGui::TreePop();
				
				
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Create Vehicle"))
			{
				App->engineSystem->GetCurrentScene()->CreateNewGameObjectVechicle();
			}
			
			/*ImGui::Separator();

			if (ImGui::TreeNode("Import Models"))
			{
				if (ImGui::MenuItem("House"))
				{
					createHouse = true;
				}
				if (ImGui::MenuItem("Gyarados"))
				{
					createGyarados = true;
				}
				if (ImGui::MenuItem("Jolteon"))
				{
					createHouse = true;
				}
				if (ImGui::MenuItem("Car_1"))
				{
					createGyarados = true;
				}
				ImGui::TreePop();

			}*/
			ImGui::Separator();
			if (ImGui::TreeNode("Effects"))
			{
				if (ImGui::MenuItem("Particles", "", false, false))
				{

				}

				ImGui::TreePop();
			}
			ImGui::Separator();
			if (ImGui::TreeNode("Light"))
			{
				if (ImGui::MenuItem("Directional Light", "", false, false))
				{

				}
				if (ImGui::MenuItem("Point Light", "", false, false))
				{

				}
				if (ImGui::MenuItem("Spotlight", "", false, false))
				{

				}
				if (ImGui::MenuItem("Area Light", "", false, false))
				{

				}
				ImGui::TreePop();
			}
			ImGui::Separator();
			if (ImGui::TreeNode("Audio"))
			{
				if (ImGui::MenuItem("Audio Source", "", false, false))
				{

				}
				if (ImGui::MenuItem("Audio Reverb Zone", "", false, false))
				{

				}
				ImGui::TreePop();
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Camera"))
			{
				GameObject* camera = App->engineSystem->GetCurrentScene()->CreateNewGameObject();
				camera->AddComponent(GOC_Type::GOC_CAMERA);
				camera->name = "Camera";
			}
			ImGui::EndMenu();
		}

		//VIEW
		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::TreeNode("Render Options"))
			{

				if (ImGui::Checkbox("AMBIENT OCLUSSION", &App->renderer3D->atributes.AmbientOclussion))
				{}

				if (ImGui::Checkbox("COLOR MATERIAL", &App->renderer3D->atributes.Color_Materials))
				{}

				if (ImGui::Checkbox("CULL FACE", &App->renderer3D->atributes.Cull_Face))
				{}

				if (ImGui::Checkbox("DEPTH TEST", &App->renderer3D->atributes.Depth_test))
				{}

				if (ImGui::Checkbox("FRONT", &App->renderer3D->atributes.Front))
				{}

				if (ImGui::Checkbox("LIGHTNING", &App->renderer3D->atributes.Lightning))
				{}

				if (ImGui::Checkbox("WIREFRAME", &App->renderer3D->atributes.Wireframe))
				{}

				ImGui::TreePop();
			}
			ImGui::Separator();
			
			if (ImGui::TreeNode("Shaders"))
			{
				if (ImGui::MenuItem("Select Edit Color", "", false, false))
				{

				}

				ImGui::TreePop();
			}
			ImGui::EndMenu();
		}

		//WINDOWS
		if (ImGui::BeginMenu("Window")) //PUEDE IR PERFECTAMENTE EN EL WINDOW DE ABAJO
		{
			if (ImGui::MenuItem("Hierarchy"))
			{
				hierarchy = !hierarchy;
			}
			ImGui::Separator();

			if (hierarchy)
			{
				/*ImVec2 textSize = ImGui::CalcTextSize("Hierarchy");
				ImVec2 windowSize = ImVec2(screenX / 4, screenY);
				ImGui::SetNextWindowPos(ImVec2((io.DisplaySize.x - windowSize.x) * 0.5f, (io.DisplaySize.y - windowSize.y)));
				ImGui::SetNextWindowSize(windowSize);*/
			}

			if (ImGui::MenuItem("Inspector"))
			{
				inspector = !inspector;
			}
			ImGui::Separator();
			
			if (ImGui::MenuItem("Assets"))
			{
				assets = !assets;
			}
			ImGui::Separator();
			
			if (ImGui::MenuItem("Show Output"))
			{
				showOutput = !showOutput;
			}
			ImGui::Separator();

			if (ImGui::MenuItem("Play & Stop"))
			{
				playStop = !playStop;
			}

			//if (showOutput)
			//{
			//	/*ImVec2 textSize = ImGui::CalcTextSize("Console");
			//	ImVec2 windowSize = ImVec2(screenX, screenY / 4);
			//	ImGui::SetNextWindowPos(ImVec2((io.DisplaySize.x - windowSize.x) * 0.5f, (io.DisplaySize.y - windowSize.y)));
			//	ImGui::SetNextWindowSize(windowSize);*/
			//}
			ImGui::EndMenu();
		}

		//HELP
		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::TreeNode("About us"))
			{
				ImGui::Text("SEPARATY ENGINE");
				ImGui::Separator();
				ImGui::Text("An engine that without hesitation, will be BETTER THAN UNITY!");
				ImGui::Separator();
				ImGui::Text("By Gerard Martinez & Brandon Arandia");
				ImGui::NewLine();

				ImGui::Text("Take a look at our github:");
				if (ImGui::Button("Github"))
				{
					App->RequestBrowser("https://github.com/IconicGIT/Separaty_Engine");  
				}
				ImGui::NewLine();

				ImGui::Text("Visit github page for detailed information regarding code and functionalities:");
				if (ImGui::Button("Github Web Page"))
				{
					App->RequestBrowser("https://iconicgit.github.io/Separaty_Engine/");
				}
				ImGui::NewLine();

				ImGui::Text("Download latest versions of the Engine here:");
				if (ImGui::Button("Latest versions"))
				{
					App->RequestBrowser("https://github.com/IconicGIT/Separaty_Engine");
				}
				/*if (ImGui::Button("l"))
				{
					App->RequestBrowser("https://github.com/IconicGIT/Separaty_Engine");
				}*/
				ImGui::NewLine();
				ImGui::Separator();
				//ImGui::NewLine();

				ImGui::Text("3rd parties libraries used:");
				//Used Libraries
				ImGui::BulletText("Assimp 5.0.1");
				/*ImGui::SameLine();
				if (ImGui::MenuItem("--> http://www.assimp.org/"))
				{
					App->RequestBrowser("http://www.assimp.org/");
				}*/
				ImGui::BulletText("DevIL 1.8.0");
				/*ImGui::SameLine();
				if (ImGui::MenuItem("--> http://openil.sourceforge.net/"))
				{
					App->RequestBrowser("http://openil.sourceforge.net/");
				}*/
				ImGui::BulletText("Glew 2.2.0");
				/*ImGui::SameLine();
				if (ImGui::MenuItem("--> http://glew.sourceforge.net/"))
				{
					App->RequestBrowser("http://glew.sourceforge.net/");
				}*/
				ImGui::BulletText("ImGui 1.89");
				/*ImGui::SameLine();
				if (ImGui::MenuItem("--> https://github.com/ocornut/imgui"))
				{
					App->RequestBrowser("https://github.com/ocornut/imgui");
				}*/
				ImGui::BulletText("Json 1.2.1");
				/*ImGui::SameLine();
				if (ImGui::MenuItem("--> https://github.com/nlohmann/json"))
				{
					App->RequestBrowser("https://github.com/nlohmann/json");
				}*/
				ImGui::BulletText("MathGeoLib 1.5");
				/*ImGui::SameLine();
				if (ImGui::MenuItem("--> https://github.com/juj/MathGeoLib"))
				{
					App->RequestBrowser("https://github.com/juj/MathGeoLib");
				}*/
				ImGui::BulletText("SDL 2.0.4"); 
				/*ImGui::SameLine();
				if (ImGui::MenuItem("--> https://www.libsdl.org/"))
				{
					App->RequestBrowser("https://www.libsdl.org/");
				}*/
				ImGui::BulletText("OpenGL 2.0");
			/*	ImGui::SameLine();
				if (ImGui::MenuItem("--> https://www.khronos.org/registry/OpenGL-Refpages/es3.0/"))
				{
					App->RequestBrowser("https://www.khronos.org/registry/OpenGL-Refpages/es3.0/");
				}*/

				/////////////////////////

				ImGui::NewLine();
				ImGui::Separator();
				//ImGui::NewLine();
				ImGui::Text("MIT License");
				ImGui::NewLine();
				ImGui::Text("Copyright (c) 2022 Brandon Arandia & Gerard Martinez");
				ImGui::NewLine();
				ImGui::Text("Permission is hereby granted, free of charge, to any person obtaining a");
				ImGui::Text("copy of this software and associated documentation files(the 'Software'),");
				ImGui::Text("to dealin the Software without restriction, including without limitation");
				ImGui::Text("the rights to use, copy, modify, merge, publish, distribute, sublicense,");
				ImGui::Text("and /or sell copies of the Software, and to permit persons to whom the");
				ImGui::Text("Software is furnished to do so, subject to the following conditions:");
				ImGui::NewLine();
				ImGui::Text("The above copyright notice and this permission notice shall be included");
				ImGui::Text("in all copies or substantial portions of the Software.");
				ImGui::NewLine();
				ImGui::Text("THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR");
				ImGui::Text("IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,");
				ImGui::Text("FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE");
				ImGui::Text("AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER");
				ImGui::Text("LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,");
				ImGui::Text("OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN");
				ImGui::Text("THE SOFTWARE.");

				
				ImGui::TreePop();
			}
			ImGui::Separator();

			if (ImGui::MenuItem("Separaty Manual"))
			{
				App->RequestBrowser("https://github.com/IconicGIT/Separaty_Engine");   
			}
			
			ImGui::Separator();

			if (ImGui::MenuItem("Make Any Comment"))
			{
				App->RequestBrowser("https://github.com/IconicGIT/Separaty_Engine/pulls");
			}

			if (ImGui::MenuItem("Report Bugs"))
			{
				App->RequestBrowser("https://github.com/IconicGIT/Separaty_Engine/issues");
			}
		
			ImGui::EndMenu();
		}

		
		ImGui::EndMainMenuBar();
	}
	
	//Calling Functions & Windows

	uiFunctions->Update(dt);

	/////
	ImGui::Render();
	//ImGui::EndFrame();
	ImGui::UpdatePlatformWindows();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return UPDATE_CONTINUE;
}

update_status ModuleUI::PostUpdate(float dt)
{
	
	return UPDATE_CONTINUE;
}

bool ModuleUI::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	for (char* listElement : outputList)
	{
		delete listElement;
	}

	return true;
}

bool  ModuleUI::SaveState(JSON_Value* file, std::string root) const
{
	std::string name = this->name;
	const char* buf = name.c_str();

	json_object_dotset_string(json_object(file), "modules.UI.name", buf);
	json_serialize_to_file(file, "project1.json");


	//json_object_dotset_number(json_object(file), "modules.Window.width", (double)width);
	//json_object_dotset_number(json_object(file), "modules.Window.height", (double)height);


	//json_serialize_to_file(file, "project1.json");

	App->ui->AppendToOutput(DEBUG_LOG("Saved UI module."));


	return true;
}

bool  ModuleUI::LoadState(JSON_Value* file, std::string root)
{
	const char* n = json_object_dotget_string(json_object(file), "modules.UI.name");

	App->ui->AppendToOutput(DEBUG_LOG("%s", n));

	return true;
}