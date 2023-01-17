#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"


#include "SDL/include/SDL_opengl.h"





ModuleSceneIntro::ModuleSceneIntro(bool start_enabled) : Module(start_enabled)
{
	name = "Scene";

}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	DEBUG_LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	//plane.SetNormal(0, 1, 0);

	/*gameObject = new GameObject();
	gameObject->Init();
	gameObject->Start();*/

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	DEBUG_LOG("Unloading Intro scene");

	for (int n = 0; n < primitives.size(); n++)
	{
		delete primitives[n];
	}
	primitives.clear();

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{

	/*gameObject->Update(dt);
	gameObject->PostUpdate(dt);*/

	//plane.Render();
	//cube.Render();
	//sphere.Render();
	////cil.Render();



	//if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT)
	//{
	//	plane.SetExtension(10);
	//	sphere.SetRadius(1);
	//	sphere.SetColumns(5);
	//	//sphere.SetRows(5);
	//	cil.SetColumns(10);
	//}
	//else
	//{
	//	plane.SetExtension(200);
	//	sphere.SetRadius(1);

	//	sphere.SetColumns(25);
	//	sphere.SetRows(25);
	//	cil.SetColumns(30);

	//}

	if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
	{
		App->SaveGameRequest();
	}

	if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
	{
		App->LoadGameRequest();
	}

	if (App->debug == true)
	{
		if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		{
		/*	glLineWidth(2.0f);
			glBegin(GL_LINES);
			glVertex3f(0.f, 0.f, 0.f);
			glVertex3f(0.f, 10.f, 0.f);
			glEnd();
			glLineWidth(1.0f);*/


		}
	}


	//TODO 3: Nothing to do here. But it's good to know where all primitives are being updated
	//for (uint n = 0; n < primitives.Count(); n++)
	//{
	//	primitives[n]->Update();
	//}

	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
	//TODO 3: Nothing to do here. But it's good to know where all primitives are being rendered
	//for (uint n = 0; n < primitives.Count(); n++)
	//{
	//	primitives[n]->Render();
	//}

	return UPDATE_CONTINUE;
}

//TODO 9: And change the color of the colliding bodies, so we can visualize it working!


bool  ModuleSceneIntro::SaveState(JSON_Value* file, std::string root) const
{

	std::string name = this->name;
	const char* buf = name.c_str();

	json_object_dotset_string(json_object(file), "modules.Scene.name", buf);
	json_serialize_to_file(file, "project1.json");


	//json_object_dotset_number(json_object(file), "modules.Window.width", (double)width);
	//json_object_dotset_number(json_object(file), "modules.Window.height", (double)height);


	//json_serialize_to_file(file, "project1.json");

	App->ui->AppendToOutput(DEBUG_LOG("Saved Scene module."));


	return true;
}

bool  ModuleSceneIntro::LoadState(JSON_Value* file, std::string root)
{
	const char* n = json_object_dotget_string(json_object(file), "modules.Scene.name");

	App->ui->AppendToOutput(DEBUG_LOG("%s", n));

	return true;
}